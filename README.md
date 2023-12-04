# Energy-Storage

This is a console application, that based on data of electricity from renewable energy
sources, can tell whether it is worth converting electricity to hydrogen.

>  This application is made as a part of our P1 Project.

## Running the program examples.

Examples on running the application:

1) Run the program, and type "`help`".
    * This prints all the possible commands available to run.
      <img alt="Help example" src="img/help.png" width=480>

2) Run the program, and type "`data`".
    * This prompts the user for a date.
    * After date has been input, data for that day will be printed on the screen.
      !["Data" Command](img/data.png "Data")
      ...
      !["Data" Command](img/data2.png "Data")
3) Run the program, and type "`simulation`".
    * This prompts the user for a start, and end date.
    * When the two dates have been input, a simulation will run through these dates, and fill a virtual
      tank with hydrogen from the excess electricity.
        * This hydrogen will then be converted back in to electricity in days of underproduction of electricity.


4) After having run "simulation", type "`status`".
    * This will print the current status of the tank.
    * <img src="img/status.png" alt="Status examples" width="400">


5) To fill the tank manually, type "`fill`".
    * This will prompt the user for the amount of hydrogen to fill the tank with.


6) To convert all hydrogen in the tank in to electricity, type "`convert`"


7) To empty the tank, type "`reset`".
    * This will reset everything in the tank.

## About the tests


## Authors
+ [Lasse Moesgaard Ørgaard](https://github.com/LasseOergaardAAU)<br/>
+ [Magnus Hyldgaard Kristensen](https://github.com/MagnusHK3)<br/>
+ [Hera Diep](https://github.com/Hera97)<br/>
+ [Christian Lucas Ry jensen](https://github.com/lucasryy)<br/>
+ [Jonas Stæhr Pedersen](https://github.com/GQ08WF)<br/>



