/*

// Oscar Laguna
#include "grabber2.h"

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
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

//Checking for Physics Handle Component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp,Warning,TEXT("No se encuentra el componente PhysicsHandle dentro de %s"),*GetOwner()->GetName());
	}
}

//Setup Actions for Input Component
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab",IE_Pressed,this,&UGrabber::Grab);
		InputComponent->BindAction("Grab",IE_Released,this,&UGrabber::Release);
	}
}

void UGrabber::Grab()
{
		UE_LOG(LogTemp,Warning,TEXT("Grabber Pressed"));
		FHitResult HitResult = GetFirstPhysicsBodyInReach();

		//TODO
		//Si golpeamos algo entonces adjuntamos el physics handle (Controlador de físicas)
		
}
	
void UGrabber::Release()
{
		UE_LOG(LogTemp,Error,TEXT("Grabber Released"));
	
		//TODO
		//Borramos-Soltamos el physics handle (Controlador de físicas)
}

	// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Si el physic handle está agarrado
		//Movemos el objeto que estamos agarrando
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	//Obtener el ViewPort de DefaultPawn_BP
	FRotator PlayerViewPointRotation;
	FVector PlayerViewPointLocation;

	//Esta función no devuelve nada, pero modifica el valor de los parametros ya que se pasan por referencia
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation,PlayerViewPointRotation);


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
	FCollisionQueryParams TraceParams(FName(""),false,GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);
	
	// Comprobar ver qué alcanzamos con el RayCast
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp,Warning,TEXT("%s"),*(ActorHit->GetName()));
	}
	return Hit;
}
	
	

*/