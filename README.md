/*------------------------------C++--------------------------------------
 *		Illinois Thermal Analysis Program - Finite Volume	
 *							ILLITHERM-FV
 *							Version 2.0
 *				Copyright (c) Sushobhan Sen, 2018
 ------------------------------------------------------------------------*/
 
 Variable definitions
 
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
 *nodes		int			number of nodes in the layer
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