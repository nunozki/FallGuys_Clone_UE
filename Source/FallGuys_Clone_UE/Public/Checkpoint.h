#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class FALLGUYS_CLONE_UE_API ACheckpoint : public AActor
{
	GENERATED_BODY()

public:
	ACheckpoint();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = "Checkpoint")
	int32 CheckpointIndex = 0;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
};