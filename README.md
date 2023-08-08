# ParkingSystem with C99

**System Explanation**

In a fully automated parking lot with an elevator, an entrance fee proportional to the weight of the vehicles (2.5 TL for 1 ton) and the fees specified in the table below are charged according to the duration of their stay in the parking lot:

|              Time             |  Fee  |
|:-----------------------------:|:-----:|
|        Less than 1 Hour       |  3 TL |
|   1 Hour - Less than 3 Hours  |  5 TL |
|  3 Hours - Less than 5 Hours  |  7 TL |
|  5 Hours - Less than 10 Hours | 10 TL |
| 10 Hours - Less than 24 Hours | 14 TL |
|       For every 24 Hours      | 15 TL |

The coefficients specified in the table below are applied to the above-mentioned time-based fees according to vehicle classes:

| Vehicle Class Code | Vehicle Class Name | Multiplier |
|:------------------:|:------------------:|:----------:|
|          1         |     Motorcycle     |      1     |
|          2         |         Car        |      2     |
|          3         |       Minibus      |      3     |
|          4         |         Bus        |      3     |
|          5         |        Truck       |      4     |
|          6         |        Lorry       |      4     |

In addition, a 100% discount is applied if the driver of motorcycles and passenger cars is a veteran and a 50% discount is applied if the driver of motorcycles and passenger cars is disabled.
<br>
<br>
After entering the information, the program will display some statistical information on the screen. 
