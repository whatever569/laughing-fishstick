#ifndef DATAMC_HPP
#define DATAMC_HPP

#define GAMEDATAINIT_TIMEOUT   30e3	//30 seconds
#define GAMEDATARETURN_TIMEOUT 20e3 //20 seconds

bool GameDataInit(void);		//takes data from pc uart to setup game
void GameDataDefault(void);
int GameDataReturn(void);		//sends data to pc for stats, temprature and such

#endif