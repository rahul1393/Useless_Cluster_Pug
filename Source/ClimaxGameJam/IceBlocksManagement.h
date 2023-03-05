// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IceTile.h"
#include "Math/Vector.h"

#include "IceBlocksManagement.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVictoryCheckCompleted, bool, IsVictory);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLIMAXGAMEJAM_API UIceBlocksManagement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIceBlocksManagement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
		void TriggerVictoryCheck(FVector IceBlockLocation);

	bool CheckIfIceBlockIsALive(UIceTile** FoundTile);
	bool RecursiveLookForAPathCircle(FVector ChosenTile, FVector PreviousTile, FVector FinalTile, FVector& MaxCoordinate, FVector& MinCoordinate, bool& IsCircleFound); // returns true if it found a circle
	bool ClearTheCentralPieces(FVector MaxCoordinate, FVector MinCoordinate); // returns true if it found  the bear tiles

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FVector, UIceTile*> IceBlocksMap;

	UPROPERTY(BlueprintAssignable)
		FOnVictoryCheckCompleted OnVictoryCheckCompleted;
		
};
