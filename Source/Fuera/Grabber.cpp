// Oscar Laguna
#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp,Warning,TEXT("No se encuentra el componente PhysicsHandle dentro de %s"),*GetOwner()->GetName());

	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Obtener el ViewPort de DefaultPawn_BP
	FRotator PlayerViewPointRotation;
	FVector PlayerViewPointLocation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation,PlayerViewPointRotation);
	//Esta función no devuelve nada, pero modifica el valor de los parametros ya que se pasan por referencia
	
	//UE_LOG(LogTemp,Warning,TEXT("%s"),*PlayerViewPointLocation.ToString());
	//UE_LOG(LogTemp,Warning,TEXT("%s"),*PlayerViewPointRotation.ToString());

	//Dibujamos una linea que vaya desde el jugador hasta una distancia (Reach) en función de su rotación
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector())*Reach;
	DrawDebugLine(GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0,255,0),
		false,
		0.0f,
		0.0f,
		5.0f);
	
	//Raycast hasta una determinada distancia (Reach)

	FHitResult Hit; //Aquí se almacenará el objeto contra el que choca el Raycast

	FCollisionQueryParams TraceParams(
		FName(""),
		false,
		GetOwner());

	bool HasImpacted = GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);
		
	// Comprobar qué alcanzamos con el RayCast

	if (HasImpacted)
	{
		FString Nombre = Hit.GetActor()->GetName();
		UE_LOG(LogTemp,Warning,TEXT("%s"),*Nombre);
	}
}

