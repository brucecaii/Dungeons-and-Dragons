#ifndef CHARACTER_ATTR_H
#define CHARACTER_ATTR_H

class CharacterAttr {

public:
	CharacterAttr();
	CharacterAttr(int intelligence, int wisdom, int strength, int dexterity, int constitution, int charisma);
	~CharacterAttr();
	bool validateAttr();
	//setter and getter
	int getIntelligence() const;
	void setIntelligence(int intelligence);
	int getWisdom() const;
	void setWisdom(int wisdom);
	int getStrength() const;
	void setStrength(int strength);
	int getDexterity() const;
	void setDexterity(int dexterity);
	int getConstitution() const;
	void setConstitution(int constitution);
	int getCharisma() const;
	void setCharisma(int charisma);

private:
	int intelligence, wisdom, strength, dexterity, constitution, charisma; //basic attr
};

#endif 