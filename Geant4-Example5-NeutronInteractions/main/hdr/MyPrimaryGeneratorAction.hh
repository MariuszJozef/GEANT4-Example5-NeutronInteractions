#ifndef MYPRIMARYGENERATORACTION_HH_
#define MYPRIMARYGENERATORACTION_HH_

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"

class G4ParticleGun;
class G4ParticleDefinition;
class G4Event;

class MyPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
public:
	MyPrimaryGeneratorAction(G4ThreeVector halfLabSize);
	~MyPrimaryGeneratorAction();

public:
	void GeneratePrimaries(G4Event* anEvent);

	G4String GetLabelParticleGunName() const { return labelParticleGunName; }
	void SetLabelParticleGunName(const G4String& labelParticleGunName) {
		this->labelParticleGunName = labelParticleGunName;
	}

	G4double GetLabelParticleGunEnergy() const { return gunEnergy; }
	void SetLabelParticleGunEnergy(G4double gunEnergy) {
		this->gunEnergy = gunEnergy;
	}

private:
	G4ParticleGun *particleGun{nullptr};

//	G4ParticleDefinition *geantino{nullptr}, *chargedGeantino{nullptr};
	G4ParticleDefinition *gamma{nullptr}, *opticalPhoton{nullptr};
//	G4ParticleDefinition *electron{nullptr}, *positron{nullptr};
	G4ParticleDefinition *proton{nullptr}, *antiProton{nullptr};
	G4ParticleDefinition *neutron{nullptr}, *antiNeutron{nullptr};
	G4ParticleDefinition *alpha{nullptr}, *antiAlpha{nullptr};
//	G4ParticleDefinition *genericIon{nullptr};

	G4double gunEnergy;
	G4ThreeVector gunPosition, halfLabSize;
	G4String labelParticleGunName;
};

#endif /* MYPRIMARYGENERATORACTION_HH_ */
