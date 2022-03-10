/*------------------------------C++--------------------------------------
 *		Illinois Thermal Analysis Program - Finite Volume	
 *							ILLITHERM-FV
 *							Version 2.0
 *				Copyright (c) Sushobhan Sen, 2018
 ------------------------------------------------------------------------*/
 
 ## Variable definitions
 
 /*------------------------granularLayersDict----------------------------
 
 *layer		int			layer number
 
 *type		string		PCC, AC, or other (doesn't go into computations)
 
 *thickness	float		thickness in meters
 
 *k			float		thermal conductivity in W/mK
 
 *rho		float		maximum dry density in kg/m3
 
 *cp		float		Specific heat capacity in J/kgK
 
 *owc		float		Optimum gravimetric water content (%)
 
 *a			float		Fredlund SWCC a coefficient
 
 *b			float 		Fredlund SWCC b coefficient
 
 *c			float 		Fredlund SWCC c coefficient
 
 *hr		float 		Fredlund SWCC hr value
 
 *PI		float		Plasticity Index
 
 *D60		float		60th percentile passing size (mm)
 
 *P200		float		Passing #200 sieve (%)
 
 *P4		float		Passing #4 sieve (%)
 
 *nodes		int			number of nodes in the layer
 
 *Variables must be comma delimited
 
 *Last layer must be of subgrade with a "large" thickness (at least 1 m or 1000 mm)
 
 -------------------------------------------------------------------------*/
 
 
 /*------------------------stabilizedLayersDict----------------------------
 
 *layer		int			layer number
 
 *type		string		PCC, AC, or other (doesn't go into computations)
 
 *thickness	float		thickness in meters
 
 *k			float		thermal conductivity in W/mK
 
 *rho		float		density in kg/m3
 
 *cp		float		Specific heat capacity in J/kgK
 
 *albedo	float		Albedo - required first layer only, set others to null
 
 *emissivity	float	Emissivity - required first layer only, set others to null
 
 *nodes		int			number of nodes in the layer (in general, node spacing should be approx 25 mm for best results)
 
 *Variables must be comma delimited
 
 -------------------------------------------------------------------------*/
 
 
 /*-------------------------------weatherDict-------------------------------
 
 *CaseNo	int		Case number (must be unique)
 
 *Year		int		Year (four digit number)
 
 *Month		int		Month (Jan = 1, Dec = 12)
 
 *Day		int		Day 
 
 *Hour		int		Hour (Midnight = 0, 11:00 PM = 23)
 
 *AirTemp	float	Air Temperature (degrees Celsius)
 
 *Wind		float	Max wind speed (m/s)
 
 *Sun		float	Percentage of sky which is NOT covered by clouds (1-cloud cover) (%)
 
 *Tdp		float	Dew point temperature (degrees Celsius)
 
 *Lat		float	Latitude as a decimal (N is positive, S is negative)
 
 *Long		float	Longitude as a decimal (E is positive, W is negative)
 
 -------------------------------------------------------------------------*/
 
 ## Instructions to run the program
 **To compile:** `make illithermfv`
 
 **To run:** `./illithermfv.out stabilizedLayersDict.csv granularLayersDict.csv weatherDict.csv output.csv`
 The first argument is the file with stabilized layer inputs, the second argument the granular layer inputs, and the third the weather inputs. All three of these **must** in the `constant/` directory, though the names can be changed (must be CSV formatted). The last argument is the name of the output file, which will always be written in CSV format regardless of the extension. 
 
 **Note on running with Windows:** In the Makefile, change *.out to *.exe and make sure to compile with Cygwin or MinGW (switch to the `Windows` branch for a version of the Makefile that does this). If porting to a different computer, compile with MinGW and include `cygwin.dll` with the package. To force the program to use the local `cygwin.dll`, copy the `illithermfv.exe` file and add the `.local` extension to it.
 
 ## Output format
 The program generates two output files containing the temperature profiles for every hour in the weather file. These are:
 - **output.csv** (or whatever is the last user argument): This will be a CSV file. The first row contains timestamp headers, followed by the depth of each node (*in mm*) from the surface. Note that this being a finite volume formulation, there is no node at the surface itself; the user can use a simple piecewise linear interpolation to calculate temperatures at other nodes. Each of the next lines (one per each record in the weather input file) contains the year, month, day, hour, and then each of the nodal temperatures for that time (*in C*).
 - **ThermalPCC_ILLITHERM.dat** (the name is hard-coded for now): This is an MEPDG-style file that directly mimics the ThermalPCC.dat file format that is used by PavementME. It contains the hourly temperature profile in the surface layer only. Temperatures (*in F*) are reported from the surface to the bottom of the topmost layer at 11 equally-spaced nodes (spacing = thickness/10). The first column contains a time stamp of the format yyyy-mm-dd-hh, again following the MEPDG format. These values are evaluated using piecewise linear interpolation, the code is contained in the `MEPDG.cpp` file.