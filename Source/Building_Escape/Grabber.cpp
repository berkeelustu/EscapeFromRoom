#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay() // Runs the functions when the Game starts.
{
	Super::BeginPlay();

    FindPhysicsHandle ();
	SetUpInputComponent ();
}

void UGrabber::SetUpInputComponent () // Sets up the input we will give to grab and release the objects.
{
	InputComponent=GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed , this, &UGrabber::Grab);
		InputComponent->BindAction("Grab",IE_Released , this, &UGrabber::Release);
	}
}

void UGrabber::FindPhysicsHandle () // Checks if the Player has the PhysicsHandle component
{
	PhysicsHandle= GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error,TEXT("%s doesn't have the component..."), *GetOwner()->GetName());
	}
}

void UGrabber::Grab() // Function to Grab Objects
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* Actorhit = HitResult.GetActor();
if(Actorhit)
{
	UE_LOG(LogTemp, Error,TEXT("Grabbed."));
	PhysicsHandle->GrabComponentAtLocation
	(
		ComponentToGrab,
		NAME_None,
		GetPlayersReach()
	);
}
}
void UGrabber::Release() // Function to release Objects
{
	UE_LOG(LogTemp, Error,TEXT("Released."));
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)  // Runs the codes in every frame in the Game
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PhysicsHandle->GrabbedComponent) 
	{
		PhysicsHandle->SetTargetLocation(GetPlayersReach());
	}

}
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;
    FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());

	FVector EndOfLineTrace = GetPlayersReach();

GetWorld()->LineTraceSingleByObjectType(
	OUT Hit,
	GetPlayersWorldPosition(),
	EndOfLineTrace,
	FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
	TraceParams
);
return Hit;
}

FVector UGrabber::GetPlayersWorldPosition() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);
	return PlayerViewPointLocation;
}

FVector UGrabber::GetPlayersReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}