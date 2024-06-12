//https://github.com/olikraus/u8g2
//bitmap to array: https://javl.github.io/image2cpp/


#include "main.h"
#include "display_u8g2.h"

char tempstr[33]; //max 32char (e.g. 4x6 font) + 0-terminator
uint32_t graph_buf[X_N];
uint32_t graph_idx;

u8g2_t u8g2_instance;                    // u8g2 object
u8g2_t* u8g2 = &u8g2_instance;
uint8_t u8g2_x, u8g2_y;         // current position on the screen


#define U8LOG_FONT u8g2_font_5x8_tr
#define U8LOG_WIDTH 25 //128/5
#define U8LOG_HEIGHT 8 //64/8
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];
u8log_t u8g2log_instance;
u8log_t* u8g2log = &u8g2log_instance;


uint8_t t_set = T_SETPONT;

//https://github.com/olikraus/u8g2/wiki/muiref
//https://github.com/olikraus/u8g2/wiki/muimanual
mui_t mui_instance;
mui_t* mui = &mui_instance;

muif_t muif_list[] = {
                      MUIF_U8G2_FONT_STYLE(0, u8g2_font_5x7_tf),
                      MUIF_LABEL(mui_u8g2_draw_text),            //simple label
                      MUIF_BUTTON("JP", mui_u8g2_btn_goto_wm_fi), //jump button (jump to form)
                      MUIF_BUTTON("BN", mui_u8g2_btn_exit_wm_fi), //exit button
                      MUIF_U8G2_U8_MIN_MAX("TS", &t_set, 0, 60, mui_u8g2_u8_min_max_wm_mud_pi) //8bit variable entry
};

fds_t fds_data[] =
    MUI_FORM(1) //Main menu -----------------------
    MUI_STYLE(0)
    MUI_LABEL(0,10, "Main Menu")
    MUI_XYAT("JP", 10, 22, 2, "Freq") //jump to form
    MUI_XYAT("JP", 10, 34, 3, "Temp") //jump to form
    MUI_XYAT("JP", 10, 46, 4, "ANTON") //jump to form
    MUI_XYAT("JP", 10, 58, 5, "GNSS") //jump to form
    MUI_FORM(2) //Frequency ---------------------
    MUI_STYLE(0)
    MUI_LABEL(0,10, "Freq")
    MUI_XYAT("JP", 9, 22, 1, "ret") //jump to main
    MUI_FORM(3) //Temperature ---------------------
    MUI_STYLE(0)
    MUI_LABEL(0,10, "T_s")
    MUI_XY("TS", 18, 10) //temp entry
    MUI_XYAT("JP", 9, 22, 1, "ret") //jump to main
    MUI_FORM(4) //Anton ---------------------
    MUI_STYLE(0)
    MUI_LABEL(0,10, "ANTON")
    MUI_XYAT("JP", 9, 22, 1, "ret") //jump to main
    MUI_FORM(5) //GNSS ---------------------
    MUI_STYLE(0)
    MUI_LABEL(0,10, "GNSS")
    MUI_XYAT("JP", 9, 22, 1, "ret") //jump to main
    ;


//globals from thd_cntr
extern uint32_t hist_buf[HIST_BUF_LEN];
extern uint32_t hist_n_samples;
extern uint32_t hist_max;

// private functions
void form_freq(int doInit);
void form_temp(int doInit);
void form_anton(int doInit);
void form_gnss(int doInit);
void form_hist_adc(int doInit);
void form_u8log(int doInit);

int global;

int display_init (void){
  //Try to detect display (default pin modes in board.h: input pulldown)
  if((palReadPad(GPIOB,GPIOB_DISP_SDA) == 0) || (palReadPad(GPIOB,GPIOB_DISP_SCL) == 0)){
    myprintf("Warning: No Display detected!\n");
    while(1){ //sleep forever. i2c would hang without display
      chThdSleepMilliseconds(1000);
    }
  }

  //working with os asserts disabled
  //todo test with ospeed lowest
  palSetPadMode(GPIOB,  GPIOB_DISP_SDA, PAL_MODE_ALTERNATE(9) | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_OTYPE_OPENDRAIN); //I2C2 SDA
  palSetPadMode(GPIOB, GPIOB_DISP_SCL, PAL_MODE_ALTERNATE(4) | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_OTYPE_OPENDRAIN); //I2C2 SCL
  chThdSleepMilliseconds(500);
  u8g2_Setup_sh1107_i2c_64x128_f(u8g2, U8G2_R1, u8x8_byte_i2c, u8x8_gpio_and_delay_stm32);// [full framebuffer, size = 1024 bytes]
  u8g2_InitDisplay(u8g2);
  u8g2_SetPowerSave(u8g2, 0);

  u8log_Init(u8g2log, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);

  mui_Init(mui, u8g2, fds_data, muif_list, sizeof(muif_list)/sizeof(muif_t));
  mui_GotoForm(mui,/* form_id= */ 1, /* initial_cursor_position= */ 0);

  //display_bootScreen(u8g2);

  return global;
}

void ThdDispFunc(void) {
  myprintf("ThdDisp\n");
  int addr = display_init();
  myprintf("display initialized. I2C_addr = %d\n", addr);

  u8g2_ClearBuffer(u8g2);
  u8g2_SetFont(u8g2, u8g2_font_helvB10_tr);
  u8g2_DrawStr(u8g2, 0,30, "start");
  u8g2_SendBuffer(u8g2);
  chThdSleepMilliseconds(200);
  int doInit = 0;

  while(true){
    if(mui_IsFormActive(mui)){
      u8g2_ClearBuffer(u8g2);
      mui_Draw(mui);
      int CurrentFormId = mui_GetCurrentFormId(mui);
      switch(CurrentFormId){
      case 1: //main
        doInit = 1;
        cntr_stop();
        gnss_forwardingDisable();
        break;
      case 2:
        form_freq(doInit);
        doInit = 0;
        break;
      case 3:
        form_temp(doInit);
        doInit = 0;
        break;
      case 4:
        form_anton(doInit);
        doInit = 0;
        break;
      case 5:
        form_gnss(doInit);
        doInit = 0;
        break;
      case 6:
        form_hist_adc(doInit);
        doInit = 0;
        break;
      case 7:
        form_u8log(doInit);
        doInit = 0;
        break;
      default:
        mui_GotoForm(mui,1,0);
        break;
      }//switch
      u8g2_SendBuffer(u8g2);
      chThdSleepMilliseconds(100);

      /* handle buttons */
      if(!palReadPad(GPIOB, GPIOB_BUTTON_A)){
        mui_NextField(mui);
      } else if(!palReadPad(GPIOB, GPIOB_BUTTON_B)){
        mui_PrevField(mui);
      } else if(!palReadPad(GPIOB, GPIOB_BUTTON_C)){
        mui_SendSelect(mui);
      }

    }
  }
}

void form_freq(int doInit){
  (void)doInit;
  if(!cntr_is_running()){
    cntr_start();
  }
  uint64_t period_fs = cntr_get_period_fs();
  float freq_hz = cntr_get_freq_hz();

  u8g2_SetFont(u8g2, u8g2_font_helvB10_tr);
  snprintf(tempstr, sizeof(tempstr), "%llu", period_fs);
  u8g2_DrawStr(u8g2, 0,30, tempstr);

  snprintf(tempstr, sizeof(tempstr), "%f", freq_hz);
  u8g2_DrawStr(u8g2, 0,50, tempstr);

  u8g2_SetFont(u8g2, u8g2_font_5x7_tf);
  u8g2_DrawStr(u8g2, 120,50, "Hz");
}

void form_anton(int doInit){
  static uint32_t n;
  if(doInit){
    n = 0;
  }

  u8g2_SetFont(u8g2, u8g2_font_helvB10_tr);
  snprintf(tempstr, sizeof(tempstr), "%5.0d", n++);
  u8g2_DrawStr(u8g2, 30,40, tempstr);
}

void form_u8log(int doInit){
  (void)doInit;
  uint8_t a,b,c,i = 0;

  a = palReadPad(GPIOB, GPIOB_BUTTON_A);
  b = palReadPad(GPIOB, GPIOB_BUTTON_B);
  c = palReadPad(GPIOB, GPIOB_BUTTON_C);

  snprintf(tempstr, sizeof(tempstr), "%u, %u, %u, %u\n", i++, a, b, c);
  u8log_WriteString(u8g2log, tempstr);
  u8g2_SetFont(u8g2, U8LOG_FONT);
  u8g2_DrawLog(u8g2, 0, 8, u8g2log);
}

void form_hist_adc(int doInit){
  (void)doInit;
  static bool flag = 0;
  if(flag){
    RCC->CR &= ~RCC_CR_HSITRIM; //clear trim (lowest freq, ca. 15.5 MHz)
    flag = 0;
  } else {
    RCC->CR &= ~RCC_CR_HSITRIM; //clear trim (lowest freq, ca. 15.5 MHz)
    RCC->CR |= RCC_CR_HSITRIM; //highest freq, ca. 17.1 MHz
    flag = 1;
  }

  uint32_t sum_bins = HIST_BUF_LEN/X_N;
  uint32_t offset = 0;
  uint32_t sum;
  uint32_t max = 0;
  for(uint32_t i=0; i<X_N; ++i){
    sum = 0;
    for(uint32_t j=0; j<sum_bins; ++j){
      sum += hist_buf[i * sum_bins + j + offset];
      if(sum > max){
        max = sum;
      }
    }
    graph_buf[i] = sum;
  }
  myprintf("hist max = %u, n_samples = %u\n", max, hist_n_samples);
  if(hist_n_samples == HIST_SAMPLES_MAX){
    myprintf("\n[");
    for(uint32_t i=0; i<HIST_BUF_LEN; ++i){
      myprintf("%u ",hist_buf[i]);
    }
    myprintf("]\n");
  }

  u8g2_SetDrawColor(u8g2, 1);
  uint32_t scale = max/(Y_N)+1;
  for(uint32_t x=0; x<X_N; ++x){
    uint16_t y = graph_buf[x]/scale;
    u8g2_DrawVLine(u8g2, x, Y_N-y, y); //x,y = top
  }
}

void form_temp(int doInit){
  const int x_graph = 43;
  const int w_graph = X_N-x_graph;
  if(doInit){
    //todo get setpoint from heater
    adc_init_temp_current();
    chThdSleepMilliseconds(1);
    for(int i = 0; i < X_N; ++i){
      graph_buf[i] = 0;
      graph_idx = 0;
    }
  }

  //todo heater module, get

  heater_setTempDegC(t_set);

  float t_heater, t_int, i_heater;
  heater_get_temp_current(&t_heater, &t_int, &i_heater);

  graph_buf[graph_idx++] = (uint32_t)t_heater;
  if(graph_idx == w_graph){
    graph_idx = 0;
  }

  myprintf("t_heater: %f, t_int: %f, v_current: %f mA\n", t_heater, t_int, i_heater);

  snprintf(tempstr, sizeof(tempstr), "T_h %.1f\n", t_heater);
  u8g2_DrawStr(u8g2, 0,36, tempstr);

  snprintf(tempstr, sizeof(tempstr), "T_i %.1f\n", t_int);
  u8g2_DrawStr(u8g2, 0,46, tempstr);

  snprintf(tempstr, sizeof(tempstr), "I    %3.0f\n", i_heater);
  u8g2_DrawStr(u8g2, 0,56, tempstr);

  //plot_graph((graph_idx-w_graph)%w_graph,x_graph, 0, w_graph, Y_N, 40, 70);
  plot_graph(u8g2, graph_idx, x_graph, 0, w_graph, Y_N, 40, 70);

  //plot heater current bar

  uint32_t h = (i_heater*Y_N)/200;
  myprintf("h: %u\n", h);
  u8g2_DrawBox(u8g2, x_graph-2, Y_N-h, 2, h);

}

void form_gnss(int doInit){
  if(doInit){
    gnss_forwardingEnable();
  }

  snprintf(tempstr, sizeof(tempstr), "tpulse %u\n", gnss_getTimepulses());
  u8g2_DrawStr(u8g2, 30,20, tempstr);

  snprintf(tempstr, sizeof(tempstr), "forward %u\n", gnss_forwardingEnabled());
  u8g2_DrawStr(u8g2, 30,32, tempstr);

  int64_t period = timer_getTimepulsePeriod();
  snprintf(tempstr, sizeof(tempstr), "per: 1s %e s\n", (float)(period - TIME_1S) * TIME_RES_F);
  u8g2_DrawStr(u8g2, 0,44, tempstr);
}
