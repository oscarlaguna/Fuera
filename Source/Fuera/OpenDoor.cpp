// Oscar Laguna
#include "OpenDoor.h"

#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "UObject/Object.h"


UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	DoorMesh = Cast<UMeshComponent>(GetOwner()->GetDefaultSubobjectByName("S_Door"));
	InitialYawn = DoorMesh->GetComponentRotation().Yaw;	
	TargetYawn = InitialYawn+RotationYaw; //Asigno la suma de la posión inicial + los grados de giro
	DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	
	PressurePlate = GetOwner()->FindComponentByClass<UBoxComponent>();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp,Error,TEXT("no encuentro"));
	}

	
	
}

float UOpenDoor::TotalMassOfActorsInVolume() const
{
	TArray<AActor*> OverlappingActors;
	if(PressurePlate)
	{
		PressurePlate->GetOverlappingActors(OverlappingActors);
	}
	
	float MassAcumulator = 0.0f;

	
		for (int i=0;i<OverlappingActors.Num();i++)
		{
			UPrimitiveComponent* ActorWithPrimitiveComponent = OverlappingActors[i]->FindComponentByClass<UPrimitiveComponent>();
			if (ActorWithPrimitiveComponent && ActorWithPrimitiveComponent->ComponentHasTag(*OpenerTag))
			{
				MassAcumulator += ActorWithPrimitiveComponent->GetMass();
			}		
		}
	
	
	return MassAcumulator;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PressurePlate && TotalMassOfActorsInVolume() > OpeningMass)
	{
		OpenDoor(DeltaTime);
		InitialTimeOpening = GetWorld()->GetTimeSeconds(); //Cuando marche del trigger me quedaré con el último valor
	} else {
		if(GetWorld()->GetTimeSeconds()>(InitialTimeOpening+ClosingDelay))
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	float NextStepYawn = FMath::FInterpTo(DoorMesh->GetComponentRotation().Yaw,TargetYawn,DeltaTime,OpenSpeed);
	FRotator OpenDoor(.0f,NextStepYawn,.0f);
	DoorMesh->SetWorldRotation(OpenDoor);
	
	if(YaHeSonado==false)
	{
		DoorSound->SetSound(OpenDoorSound);
		DoorSound->Play();
		YaHeSonado = true;
	}	
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	float NextStepYawn = FMath::FInterpTo(DoorMesh->GetComponentRotation().Yaw,InitialYawn,DeltaTime,CloseSpeed);
	FRotator OpenDoor(.0f,NextStepYawn,.0f);
	DoorMesh->SetWorldRotation(OpenDoor);
	
	//GetOwner()->SetActorRotation(OpenDoor);

	if(YaHeSonado==true)
	{
		DoorSound->SetSound(CloseDoorSound);
		DoorSound->Play();
		YaHeSonado=false;
	}
}