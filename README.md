# Table-Status Syetem 
- This Table Status System will allow the host to instantly know the status of every table in the restaurant without leaving the host station. 
- This system will eliminate the need to confirm the availability of each table in the restaurant by visual inspection, thereby streamlining the seating process and frictionless customer experience.
 
## Requirements 

### Hardware
- **Handheld RFID scanners** 
  - Each will contain an RFID scanner and wifi module to scan the tables and send a signal with the table ID to the central controller. 
- **Host Station Display** 
  - The central controller will send a signal to the display module to update the status of the tables  
- **Central Module**
  - Store and process all system information 
- Charging bank for RFID scanners
- **Software**
  - Create a website where each restaurant can acess their account to view their tables.
  - in their account they can observe and change the status of their tables
  - they can link this information about their tables to other apps such as waitlist apps 

#### Host Station 
 - A computer web application would be best, but the first itteration will include the following:
 - Located at the host station, the host will have access to an array of LEDs superimposed on the table map which will represent the table status (vacant/occupied) 
   - Each LED will have a corresponding switch to toggle the LED indicating the Table status.

#### Table Module (Update Dec 17)
- Each table will have a uniquely identified RFID sticker in a discrete location on the table.
- The RFID stickers can be rewritten in case tables are split or the layout changes. 
- These RFID stickers are completely passive and require no power or maintenance. 

#### RFID Scanner
- This module should be the size of a smartphone and battery powered.
- This will be used to scan the RFID tag on the table once the table is cleaned and ready to be seated again.
- After scanning the table, the identifier will be sent to the central module to toggle the status of the table. a confirmation will be sent back to the RFID module from the central controller indicating the new status using a coloured LED. (red =occupied, green=available)





## Methods
<img width="826" alt="image" src="https://user-images.githubusercontent.com/73149111/204847322-6f635f2e-6b91-4962-8aa1-f948ca3cb118.png">



## Materials
- Esp32/82 notsure yet
- switch bank
- lots of LEDs 
- power supply 


## Resources
http://esp32.net/

https://github.com/agucova/awesome-esp

https://esphome.io/

https://esphome.io/guides/diy.html

https://frenck.dev/diy-smart-doorbell-for-just-2-dollar/#1-smart-doorbell-stuff-youll-need

https://hackaday.io/projects?tag=ESP32
