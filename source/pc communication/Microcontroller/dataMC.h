#ifndef DATAMC_HPP
#define DATAMC_HPP

#define GAMEDATARETURN_TIMEOUT 20e3 //20 seconds

bool GameDataInit(void);		//takes data from pc uart to setup game
int GameDataReturn(void);		//sends data to pc for stats, temprature and such

#endif