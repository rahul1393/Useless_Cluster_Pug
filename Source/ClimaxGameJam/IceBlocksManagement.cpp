// Fill out your copyright notice in the Description page of Project Settings.


#include "IceBlocksManagement.h"

// Sets default values for this component's properties
UIceBlocksManagement::UIceBlocksManagement()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UIceBlocksManagement::BeginPlay()
{
	Super::BeginPlay();	
}


void UIceBlocksManagement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UIceBlocksManagement::TriggerVictoryCheck(FVector IceBlockLocation)
{
	TArray<bool> NeighbourBlocksAreAlive;
	TArray<UIceTile**> Neighbours;
	TArray<FVector> NeighboursCoordinates;

	NeighboursCoordinates.Add(FVector(IceBlockLocation.X, IceBlockLocation.Y + 100, IceBlockLocation.Z));
	NeighboursCoordinates.Add(FVector(IceBlockLocation.X, IceBlockLocation.Y - 100, IceBlockLocation.Z));
	NeighboursCoordinates.Add(FVector(IceBlockLocation.X + 100, IceBlockLocation.Y, IceBlockLocation.Z));
	NeighboursCoordinates.Add(FVector(IceBlockLocation.X - 100, IceBlockLocation.Y, IceBlockLocation.Z));

	Neighbours.Add(IceBlocksMap.Find(NeighboursCoordinates[0]));
	Neighbours.Add(IceBlocksMap.Find(NeighboursCoordinates[1]));
	Neighbours.Add(IceBlocksMap.Find(NeighboursCoordinates[2]));
	Neighbours.Add(IceBlocksMap.Find(NeighboursCoordinates[3]));

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
		bool FoundCircle = false;
		bool IsCircleFound = false;
		FVector MaxCoordinates = IceBlockLocation;
		FVector MinCoordinates = IceBlockLocation;

		// TODO potential for Async maybe?
		for (size_t i = 0; i < Neighbours.Num(); i++)
		{
			if (!NeighbourBlocksAreAlive[i])
			{
				FoundCircle = RecursiveLookForAPathCircle(NeighboursCoordinates[i], IceBlockLocation, IceBlockLocation, MaxCoordinates, MinCoordinates, IsCircleFound);
				CountingDeadNeighbours--;

				if (FoundCircle)
				{
					IsVictory = ClearTheCentralPieces(MaxCoordinates, MinCoordinates);
					break;
				}
				else if (CountingDeadNeighbours < 2)
				{
					break;
				}
			}
		}
	}

	OnVictoryCheckCompleted.Broadcast(IsVictory);

}

bool UIceBlocksManagement::CheckIfIceBlockIsALive(UIceTile** FoundTile)
{
	bool BoolToAdd = true;

	if (FoundTile == nullptr)
	{
		BoolToAdd = true; // edges and pools inside of the grid are not counted as gaps
	}
	else
	{
		BoolToAdd = (*FoundTile)->IsLivingBlock;
	}
	return BoolToAdd;
}

bool UIceBlocksManagement::RecursiveLookForAPathCircle(FVector ChosenTile, FVector PreviousTile, FVector FinalTile, FVector& MaxCoordinate, FVector& MinCoordinate, bool& IsCircleFound)
{
	if (IsCircleFound)
	{
		return true;
	}

	TArray<bool> NeighbourBlocksAreAlive;
	TArray<UIceTile**> Neighbours;
	TArray<FVector> NeighboursCoordinates;

	NeighboursCoordinates.Add(FVector(ChosenTile.X, ChosenTile.Y + 100, ChosenTile.Z));
	NeighboursCoordinates.Add(FVector(ChosenTile.X, ChosenTile.Y - 100, ChosenTile.Z));
	NeighboursCoordinates.Add(FVector(ChosenTile.X + 100, ChosenTile.Y, ChosenTile.Z));
	NeighboursCoordinates.Add(FVector(ChosenTile.X - 100, ChosenTile.Y, ChosenTile.Z));

	Neighbours.Add(IceBlocksMap.Find(NeighboursCoordinates[0]));
	Neighbours.Add(IceBlocksMap.Find(NeighboursCoordinates[1]));
	Neighbours.Add(IceBlocksMap.Find(NeighboursCoordinates[2]));
	Neighbours.Add(IceBlocksMap.Find(NeighboursCoordinates[3]));

	NeighbourBlocksAreAlive.Add(CheckIfIceBlockIsALive(Neighbours[0]));
	NeighbourBlocksAreAlive.Add(CheckIfIceBlockIsALive(Neighbours[1]));
	NeighbourBlocksAreAlive.Add(CheckIfIceBlockIsALive(Neighbours[2]));
	NeighbourBlocksAreAlive.Add(CheckIfIceBlockIsALive(Neighbours[3]));

	bool FoundCircle = false;
	int CountingDeadNeighbours = 0;

	for (size_t i = 0; i < Neighbours.Num(); i++)
	{
		if (!NeighbourBlocksAreAlive[i])
		{
			CountingDeadNeighbours++;
		}
	}

	if (CountingDeadNeighbours > 1)
	{
		// TODO potential for Async maybe?
		for (size_t i = 0; i < Neighbours.Num(); i++)
		{
			if (!NeighbourBlocksAreAlive[i] && NeighboursCoordinates[i] != PreviousTile)
			{
				if (NeighboursCoordinates[i] == FinalTile)
				{
					IsCircleFound = true;
					return true;
				}
				else
				{
					// X coordinates check
					if (ChosenTile.X > MaxCoordinate.X)
					{
						MaxCoordinate.X = ChosenTile.X;
					}
					else if (ChosenTile.X < MinCoordinate.X)
					{
						MinCoordinate.X = ChosenTile.X;
					}

					// Y coordinates check
					if (ChosenTile.Y > MaxCoordinate.Y)
					{
						MaxCoordinate.Y = ChosenTile.Y;
					}
					else if (ChosenTile.Y < MinCoordinate.Y)
					{
						MinCoordinate.Y = ChosenTile.Y;
					}

					FoundCircle = RecursiveLookForAPathCircle(NeighboursCoordinates[i], ChosenTile, FinalTile, MaxCoordinate, MinCoordinate, IsCircleFound);
				}
			}
		}
	}

	return FoundCircle;
}

bool UIceBlocksManagement::ClearTheCentralPieces(FVector MaxCoordinate, FVector MinCoordinate)
{
	bool FoundTheBear = false;

	for (size_t i = MinCoordinate.X; i < MaxCoordinate.X; i = i + 100)
	{
		for (size_t j = MinCoordinate.Y; j < MaxCoordinate.Y; j = j + 100)
		{
			UIceTile** FoundTile = IceBlocksMap.Find(FVector(i, j, MaxCoordinate.Z));
			if (FoundTile != nullptr)
			{
				if ((*FoundTile)->IsLivingBlock)
				{
					FoundTheBear = (*FoundTile)->IsBearBlock;
					(*FoundTile)->KillIceBlock();
				}
			}
		}
	}
	return FoundTheBear;
}