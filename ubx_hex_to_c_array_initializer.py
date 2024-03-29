# -*- coding: utf-8 -*-
"""
Created on Thu Mar 28 18:23:07 2024

@author: patri
"""



#NMEA GSV disable
s = '24 50 55 42 58 2C 34 30 2C 47 53 56 2C 30 2C 30 2C 30 2C 30 2C 30 2C 30 2A 35 39 0D 0A'

#NMEA GSA disable
s = '24 50 55 42 58 2C 34 30 2C 47 53 41 2C 30 2C 30 2C 30 2C 30 2C 30 2C 30 2A 34 45 0D 0A'

#NMEA GLL disable
s = '24 50 55 42 58 2C 34 30 2C 47 4C 4C 2C 30 2C 30 2C 30 2C 30 2C 30 2C 30 2A 35 43 0D 0A'

#NMEA GGA disable
s = '24 50 55 42 58 2C 34 30 2C 47 47 41 2C 30 2C 30 2C 30 2C 30 2C 30 2C 30 2A 35 41 0D 0A'


#NMEA RMC disable
s = '24 50 55 42 58 2C 34 30 2C 52 4D 43 2C 30 2C 30 2C 30 2C 30 2C 30 2C 30 2A 34 37 0D 0A'

#NMEA VTG disable
s = '24 50 55 42 58 2C 34 30 2C 56 54 47 2C 30 2C 30 2C 30 2C 30 2C 30 2C 30 2A 35 45 0D 0A'


s = ', '.join(['0x{}'.format(i) for i in s.split()])
print('{'+ s + '}')