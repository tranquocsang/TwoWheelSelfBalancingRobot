#ifndef EEPROM_H_
#define EEPROM_H_

#define User_Password_EEPROM	0x40

extern void EEPROMConfig();
extern void loadMotorModel();
extern void saveMotorModel();

extern void Save_User(uint8_t *user, uint8_t *password);
extern uint8_t Load_All_User(uint32_t *user_password);

#endif /* EEPROM_H_ */
