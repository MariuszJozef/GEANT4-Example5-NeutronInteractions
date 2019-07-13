#include "MyPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction(G4ThreeVector halfLabSize)
:
halfLabSize(halfLabSize),
gunEnergy(16*MeV),
gunPosition(G4ThreeVector(0, 0, -halfLabSize.z()))
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;

//	geantino 		= particleTable->FindParticle(particleName="geantino");
//	chargedGeantino = particleTable->FindParticle(particleName="chargedgeantino");
	gamma 			= particleTable->FindParticle(particleName="gamma");
	opticalPhoton 	= particleTable->FindParticle(particleName="opticalphoton");
//	electron 		= particleTable->FindParticle(particleName="e-");
//	positron 		= particleTable->FindParticle(particleName="e+");
	proton 			= particleTable->FindParticle(particleName="proton");
	antiProton 		= particleTable->FindParticle(particleName="anti_proton");
	neutron 		= particleTable->FindParticle(particleName="neutron");
	antiNeutron 	= particleTable->FindParticle(particleName="anti_neutron");
	alpha 			= particleTable->FindParticle(particleName="alpha");
	antiAlpha		= particleTable->FindParticle(particleName="anti_alpha");
//	genericIon 		= particleTable->FindParticle(particleName="GenericIon");

	G4ParticleDefinition *particle = neutron;

	particleGun = new G4ParticleGun(1);
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticleEnergy(gunEnergy);
	particleGun->SetParticlePosition(gunPosition);
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
	delete particleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	G4ThreeVector gunDirection = G4ThreeVector(0, 0, 1);
	gunDirection += 0.2 * G4ThreeVector(G4UniformRand() - 0.5, G4UniformRand() - 0.5, 0);
	particleGun->SetParticleMomentumDirection(gunDirection);

	particleGun->GeneratePrimaryVertex(anEvent);

//	Display particle name and energy labels
	SetLabelParticleGunName(
			particleGun->GetParticleDefinition()->GetParticleName());
	SetLabelParticleGunEnergy(particleGun->GetParticleEnergy());
}

