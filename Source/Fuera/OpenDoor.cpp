// Oscar Laguna
#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

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
	//FRotator CurrentRotation = GetOwner()->GetActorRotation();
	//UE_LOG(LogTemp, Warning, TEXT("%s"),*CurrentRotation.ToString());
	//FRotator OpenDoor(0.0f,-90.0f,0.0f);
	//GetOwner()->SetActorRotation(OpenDoor);
	
	InitialYawn = GetOwner()->GetActorRotation().Yaw; //Inicializo la vble a la posición inicial de la puerta
	TargetYawn = InitialYawn+RotationYaw; //Asigno la suma de la posión inicial + los grados de giro
	if(!ActorThatOpenDoor)
	{
		ActorThatOpenDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate->IsOverlappingActor(ActorThatOpenDoor))
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
	//UE_LOG(LogTemp, Warning, TEXT("%s"),*GetOwner()->GetActorRotation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Yaw is %f"),GetOwner()->GetActorRotation().Yaw);
	//float NextStepYawn = FMath::Lerp(GetOwner()->GetActorRotation().Yaw,TargetYawn,.1f);
	
	float NextStepYawn = FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw,TargetYawn,DeltaTime,OpenSpeed);
	FRotator OpenDoor(.0f,NextStepYawn,.0f);
	GetOwner()->SetActorRotation(OpenDoor);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	float NextStepYawn = FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw,InitialYawn,DeltaTime,CloseSpeed);
	FRotator OpenDoor(.0f,NextStepYawn,.0f);
	GetOwner()->SetActorRotation(OpenDoor);
}

