#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

UGrabber::UGrabber()
{}

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
	if(PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error,TEXT("%s doesn't have the component..."), *GetOwner()->GetName());
	}
}

void UGrabber::Grab() // Function to Grab Objects
{
	GetPlayersReach();
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
if(HitResult.GetActor())
{
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
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)  // Runs the codes in every frame in the Game
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetPlayersReach();
	if(PhysicsHandle->GrabbedComponent) 
	{
		PhysicsHandle->SetTargetLocation(GetPlayersReach());
	}

}
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	
	GetPlayersReach();
	FHitResult Hit;
    FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());

GetWorld()->LineTraceSingleByObjectType(
	OUT Hit,
	GetPlayersWorldPosition(),
	GetPlayersReach(),
	FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
	TraceParams
);
AActor* ActorHit= Hit.GetActor();
return Hit;
}

FVector UGrabber::GetPlayersWorldPosition() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector UGrabber::GetPlayersReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}