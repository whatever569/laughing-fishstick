#ifndef DATAMC_HPP
#define DATAMC_HPP

bool GameDataInit(void);		//takes data from pc uart to setup game
void GameDataReturn(void);		//sends data to pc for stats, temprature and such

#endif