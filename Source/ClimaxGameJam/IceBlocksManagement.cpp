// Fill out your copyright notice in the Description page of Project Settings.


#include "IceBlocksManagement.h"

// Sets default values for this component's properties
UIceBlocksManagement::UIceBlocksManagement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UIceBlocksManagement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UIceBlocksManagement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UIceBlocksManagement::TriggerVictoryCheck(FVector IceBlockLocation)
{
	TArray<bool> NeighbourBlocksAreAlive;
	TArray<UIceTile**> Neighbours;

	Neighbours.Add(IceBlocksMap.Find(FVector(IceBlockLocation.X - 100, IceBlockLocation.Y, IceBlockLocation.Z)));
	Neighbours.Add(IceBlocksMap.Find(FVector(IceBlockLocation.X + 100, IceBlockLocation.Y, IceBlockLocation.Z)));
	Neighbours.Add(IceBlocksMap.Find(FVector(IceBlockLocation.X, IceBlockLocation.Y - 100, IceBlockLocation.Z)));
	Neighbours.Add(IceBlocksMap.Find(FVector(IceBlockLocation.X, IceBlockLocation.Y + 100, IceBlockLocation.Z)));

	NeighbourBlocksAreAlive.Add(CheckIfIceBlockIsALive(Neighbours[0]));
	NeighbourBlocksAreAlive.Add(CheckIfIceBlockIsALive(Neighbours[1]));
	NeighbourBlocksAreAlive.Add(CheckIfIceBlockIsALive(Neighbours[2]));
	NeighbourBlocksAreAlive.Add(CheckIfIceBlockIsALive(Neighbours[3]));

	bool IsVictory = false;
	int CountingDeadNeighbours = 0;

	for (size_t i = 0; i < Neighbours.Num() ; i++)
	{
		if (!NeighbourBlocksAreAlive[i] )
		{
			CountingDeadNeighbours++;
		}
	}

	if (CountingDeadNeighbours > 1)
	{
		for (size_t i = 0; i < Neighbours.Num(); i++)
		{
			if (!NeighbourBlocksAreAlive[i])
			{
				// TODO if one of them is the edge piece...?? mark the final as the edge piece
				//AActor* Some = (*Neighbours[i])->GetOwner();
				//RecursiveLookForAPathCircle(, IceBlockLocation, IceBlockLocation);
			}
		}
	}

	// TODO potential for Async
	OnVictoryCheckCompleted.Broadcast(IsVictory);

}

bool UIceBlocksManagement::CheckIfIceBlockIsALive(UIceTile** FoundTile)
{
	bool BoolToAdd = true;

	if (FoundTile == nullptr)
	{
		BoolToAdd = false;
	}
	else
	{
		BoolToAdd = (*FoundTile)->IsLivingBlock;
	}
	return BoolToAdd;
}

bool UIceBlocksManagement::RecursiveLookForAPathCircle(FVector ChosenTile, FVector PreviousTile, FVector FinalTile)
{
	TArray<bool> NeighbourBlocksAreAlive;

	UIceTile** FoundTile1 = IceBlocksMap.Find(FVector(ChosenTile.X - 100, ChosenTile.Y, ChosenTile.Z));
	UIceTile** FoundTile2 = IceBlocksMap.Find(FVector(ChosenTile.X + 100, ChosenTile.Y, ChosenTile.Z));
	UIceTile** FoundTile3 = IceBlocksMap.Find(FVector(ChosenTile.X, ChosenTile.Y - 100, ChosenTile.Z));
	UIceTile** FoundTile4 = IceBlocksMap.Find(FVector(ChosenTile.X, ChosenTile.Y + 100, ChosenTile.Z));

	NeighbourBlocksAreAlive.Add(CheckIfIceBlockIsALive(FoundTile1));
	NeighbourBlocksAreAlive.Add(CheckIfIceBlockIsALive(FoundTile2));
	NeighbourBlocksAreAlive.Add(CheckIfIceBlockIsALive(FoundTile3));
	NeighbourBlocksAreAlive.Add(CheckIfIceBlockIsALive(FoundTile4));

	int CounterOfLivingNeighbours = 0;

	for (bool IsLivingNeighbour : NeighbourBlocksAreAlive)
	{
		if (IsLivingNeighbour)
		{
			CounterOfLivingNeighbours++;
		}
	}

	// less than 2 means there is no path to take
	if (CounterOfLivingNeighbours < 2)
	{
		return false;
	}

	return false;
}
