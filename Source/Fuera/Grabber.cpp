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
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle(); //Busco si el defaultPawn tiene un PhysicsHandle
	SetupInputComponent(); //Comprobamos el funcionamiento del InputComponent
}
//Comprobamos el funcionamiento del InputComponent
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab",IE_Pressed,this,&UGrabber::Grab);
		InputComponent->BindAction("Grab",IE_Released,this,&UGrabber::Release);
	}	
}

//Busco si el defaultPawn tiene un PhysicsHandle
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp,Warning,TEXT("No se encuentra el componente PhysicsHandle dentro de %s"),*GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp,Error,TEXT("Se ha pulsado una tecla agarrar algo"));
	FHitResult Hit=GetFirstPhysicsBodyInReach();
	if(Hit.GetActor())
	{
		UE_LOG(LogTemp,Warning, TEXT("Estas mirando a %s"),*Hit.GetActor()->GetName());
		UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();
		if (PhysicsHandle)
		{
			PhysicsHandle->GrabComponentAtLocation(ComponentToGrab,NAME_None,GetPlayersReach());
		}		
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit; //Aquí se almacenará el objeto contra el que choca el Raycast

	FCollisionQueryParams TraceParams(
		FName(""),
		false,
		GetOwner());

	// Comprobar qué alcanzamos con el RayCast
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		GetPlayersWorldPosition(),
		GetPlayersReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);	

	//Actor contra el que choca el Raycast
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		FString Nombre = Hit.GetActor()->GetName();
		UE_LOG(LogTemp,Warning,TEXT("%s"),*Nombre);
	}
	return Hit;
}

FVector UGrabber::GetPlayersWorldPosition() const
{
	//Obtener el ViewPort de DefaultPawn_BP
	FRotator PlayerViewPointRotation;
	FVector PlayerViewPointLocation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation,PlayerViewPointRotation);
	//Esta función no devuelve nada, pero modifica el valor de los parametros ya que se pasan por referencia

	return PlayerViewPointLocation;
}

void UGrabber::Release()
{
	UE_LOG(LogTemp,Error,TEXT("Se ha soltado la tecla de agarrar"));
	if (PhysicsHandle)
	{
		PhysicsHandle->ReleaseComponent();	
	}
	
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetPlayersReach());
	}	
}

FVector UGrabber::GetPlayersReach () const
{
	//Obtener el ViewPort de DefaultPawn_BP
	FRotator PlayerViewPointRotation;
	FVector PlayerViewPointLocation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation,PlayerViewPointRotation);
	//Esta función no devuelve nada, pero modifica el valor de los parametros ya que se pasan por referencia

	//Vector hasta el objeto que esté a una determinada distancia (Reach)
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector())*Reach;
	return LineTraceEnd;
}


