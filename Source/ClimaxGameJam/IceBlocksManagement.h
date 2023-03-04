// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IceTile.h"
#include "Math/Vector.h"

#include "IceBlocksManagement.generated.h"


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
		bool IsVictory(FVector IceBlockLocation);

	bool CheckIfIceBlockIsALive(UIceTile* FoundTile);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FVector, UIceTile*> IceBlocksMap;
		
};
