#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "FGCharacter.h"

ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	RootComponent = Trigger;
	Trigger->SetBoxExtent(FVector(100.f));
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
}

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (AFGCharacter* FGChar = Cast<AFGCharacter>(OtherActor))
	{
		// Example: FGChar->SetCheckpointLocation(GetActorLocation());
		UE_LOG(LogTemp, Log, TEXT("Checkpoint %d marked!"), CheckpointIndex);
	}
}
