// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Esto es un Warning"));
	//UE_LOG(LogTemp, Error, TEXT("Esto es un mensaje de Error"));
	//UE_LOG(LogTemp, Display, TEXT("Esto es un mensaje normal"));

	UE_LOG(LogTemp,Warning,TEXT("%s"),*GetOwner()->GetTransform().GetLocation().ToString());


	
	UE_LOG(LogTemp,Warning,TEXT("%s"),*GetOwner()->GetActorLocation().ToString());



	
	//FString Nombre = GetOwner()->GetName();
	//UE_LOG(LogTemp,Warning,TEXT("%s"),*Nombre);	

	


	//FString Log = TEXT("Hola");
	//FString* PtroLog = &Log;

	//int32 longitud = Log.Len();ss
	//int32 longitud2 = (*PtroLog).Len();
	//int32 longitud3 = PtroLog->Len();
	//UE_LOG(LogTemp,Warning,TEXT("%d"),longitud);
	//UE_LOG(LogTemp,Warning,TEXT("%d"),longitud2);
	//UE_LOG(LogTemp,Warning,TEXT("%d"),longitud3);

	
	//UE_LOG(LogTemp,Warning,TEXT("%s"),*Log);
	//UE_LOG(LogTemp,Warning,TEXT("%s"),**PtroLog);

	
	
	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

