#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Grabber.h"
#define OUT


UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    FindPhysicsHandle ();
	SetUpInputComponent ();
}

void UGrabber::SetUpInputComponent ()
{
	InputComponent=GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed , this, &UGrabber::Grab);
		InputComponent->BindAction("Grab",IE_Released , this, &UGrabber::Release);
	}
}

void UGrabber::FindPhysicsHandle ()
{
	PhysicsHandle= GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle)
	{
	}
	else
	{
		UE_LOG(LogTemp, Error,TEXT("%s doesn't have the component..."), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning,TEXT("I grab the item"));
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("I release the item."));
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetFirstPhysicsBodyInReach();
}
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(OUT PlayerViewPointLocation,OUT PlayerViewPointRotation);

	FVector LineTraceEnd=PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	FHitResult Hit;
FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());

GetWorld()->LineTraceSingleByObjectType(
	OUT Hit,
	PlayerViewPointLocation,
	LineTraceEnd,
	FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
	TraceParams
);

AActor* ActorHit= Hit.GetActor();


if(ActorHit)
{
	UE_LOG(LogTemp,Warning,TEXT("This is %s ."), *(ActorHit->GetName()));
}

return Hit;
}
