#pragma once
#include "pointwell.h"	
#include "statblock.h"
#include <cstdint>
#include <memory>
#include <string>

typedef std::uint64_t exptype;
typedef std::uint16_t leveltype;

class PlayerCharacterDelegate : public StatBlock{
public:

	static const exptype LEVEL2AT = 100u;
	
	PlayerCharacterDelegate() : StatBlock(0u, 0u){
		CurrentLevel = 1u;
		CurrentEXP = 0u;
		EXPToNextLevel = LEVEL2AT;
		HP = std::make_unique<PointWell>();
	}

	void gainEXP(exptype gained_exp) {
		CurrentEXP += gained_exp;
		while(check_if_leveled()){}	
	}

	leveltype getLevel() {
		return CurrentLevel;
	}

	exptype	getCurrentEXP() {
		return CurrentEXP;
	}
	
	exptype getEXPToNextLevel() {
		return EXPToNextLevel;
	}

	virtual void LevelUp() = 0;
	virtual std::string getClassName() = 0;

	std::unique_ptr<PointWell> HP;


protected:
	leveltype CurrentLevel;
	exptype CurrentEXP;
	exptype EXPToNextLevel;

	bool check_if_leveled() {
		static const leveltype LEVELSCALAR = 2u;
		if (CurrentEXP >= EXPToNextLevel) {
			CurrentLevel++;
			LevelUp();
			EXPToNextLevel *= LEVELSCALAR;
			return true;
		}
		return false;
	}
};
class Cleric : public PlayerCharacterDelegate {
public:

	static const welltype BASEHP = (welltype)14u;
	static const stattype BASESTR = (stattype)2u;
	static const stattype BASEINT = (stattype)3u;


	Cleric(): PlayerCharacterDelegate() {
		HP->setMax(BASEHP);
		HP->increaseCurrent(BASEHP);
		increaseStats(BASESTR, BASEINT);
	}

	std::string getClassName() override { return std::string("Cleric"); }


private:
	void LevelUp() override {
		HP->setMax((welltype)BASEHP/2.f + HP->getMax());
		increaseStats((stattype)((BASESTR+1u)/2.f), (stattype)((BASEINT+1u)/2.f));
	}
};

class PlayerCharacter {
private:
	PlayerCharacterDelegate* pcclass;

public:
	PlayerCharacter() = delete;
	PlayerCharacter(PlayerCharacterDelegate* pc) : pcclass(pc) {}
	~PlayerCharacter() { delete pcclass; pcclass = nullptr; }

	std::string getClassName() { return pcclass->getClassName(); }
	leveltype getLevel() { return pcclass->getLevel(); }
	exptype getCurrentEXP() { return pcclass->getCurrentEXP(); }
	exptype getEXPToNextLevel() { return pcclass->getEXPToNextLevel(); }
	welltype getCurrentHP() { return pcclass->HP->getCurrent(); }
	welltype getMaxHP() { return pcclass->HP->getMax(); }
	stattype getStrength() { return pcclass->getStrength(); }
	stattype getIntellect() { return pcclass->getIntellect(); }

	void gainEXP(exptype amt) { pcclass->gainEXP(amt); }
	void takeDamage(welltype amt) { pcclass->HP->reduceCurrent(amt);}
	void heal(welltype amt) { pcclass->HP->increaseCurrent(amt); }



};