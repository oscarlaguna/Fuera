// Oscar Laguna
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"

#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUERA_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	
private:
	UPROPERTY(EditAnywhere);
	float RotationYaw = -90.0f; //Inicializo los grados que quiero que se abra la puerta
	float InitialYawn;	//Declaro una vble para guardar la posición inicial de la puerta
	float TargetYawn;	//Declaro una vble para guardar la posición objetivo (final) de la puerta que
	

	//será la suma de las 2 anteriores
	UPROPERTY(EditAnywhere);
	float OpenSpeed = 2.0f; //Velocidad de apertura

	UPROPERTY(EditAnywhere);
	float CloseSpeed = 2.0f; //Velocidad de cierre

	UPROPERTY(EditAnywhere);
	UBoxComponent* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere);
	AActor* ActorThatOpenDoor = nullptr;

	float InitialTimeOpening;
	
	UPROPERTY(EditAnywhere);
	float ClosingDelay = 2.0f; //Tiempo que pasa antes de que la puerta comience a cerrarse

	UPROPERTY(EditAnywhere);
	float OpeningMass = 50.0f;

	float TotalMassOfActorsInVolume() const;

	UAudioComponent* DoorSound=nullptr;
	bool YaHeSonado = false;

	UPROPERTY(EditAnywhere);
	USoundBase* OpenDoorSound =nullptr;

	UPROPERTY(EditAnywhere);
	USoundBase* CloseDoorSound=nullptr;

	UPROPERTY()
	UMeshComponent* DoorMesh = nullptr;

	UPROPERTY(EditAnywhere)
	FString OpenerTag="DoorOpener";
	
	
};