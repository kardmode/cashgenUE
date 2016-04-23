// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "cashgenUE.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Point.h"
#include "ZoneBlock.h"
#include "ZoneConfig.h"
#include "MeshData.h"
#include "ZoneManager.generated.h"


class AWorldManager;
struct GridRow
{
	TArray<ZoneBlock> blocks;
};

enum eLODStatus { BUILDING_REQUIRES_CREATE, READY_TO_DRAW_REQUIRES_CREATE, BUILDING, READY_TO_DRAW, IDLE, PENDING_DRAW_REQUIRES_CREATE, PENDING_DRAW, DRAWING_REQUIRES_CREATE, DRAWING };

UCLASS()
class CASHGENUE_API AZoneManager : public AActor
{
	GENERATED_BODY()
	// Procedural mesh component for terrain and water meshes
	//UProceduralMeshComponent* MyProcMesh;

	TMap<uint8, UProceduralMeshComponent*> MyProcMeshComponents;
	// List of instanced mesh components for spawning foliage and other meshes
	TArray<UInstancedStaticMeshComponent*> MyInstancedMeshComponents;

	// Zone configuration parameters
	FZoneConfig MyConfig;

	// Worker thread for building mesh data
	FRunnableThread* Thread;
	// For tracking blocks that still need to be processed for foliage spawning
	int32 MyBlocksToSpawnFoliageOn;
	
	AWorldManager* MyWorldManager;
	

	void PopulateZoneData(const uint8 aLOD);
	void PopulateMeshData(const uint8 aLOD);
	void InitialiseBlockPointers(const uint8 aLOD);
	void CalculateTriangles(const uint8 aLOD);

	TMap<uint8, TArray<GridRow>> MyLODZoneData;
	TMap<uint8, FMeshData> MyLODMeshData;
	
	void CreateWaterPlane(const float aWaterHeight);
	bool SpawnTreesAtIndex(int32* aIndex);
	bool GetGodCastHitPos(const FVector aVectorToStart, FVector* aHitPos, FVector* aNormalVector);

public:	
	// Sets default values for this actor's properties
	AZoneManager();
	~AZoneManager();
	bool isStale = false;
	Point MyOffset;
	TMap<uint8, eLODStatus> MyLODMeshStatus;
	uint8 currentlyDisplayedLOD;
	int32 MyZoneID;

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	
	void SetupZone(int32 aZoneID, AWorldManager* aWorldManager, const Point aOffset, FZoneConfig aZoneConfig);
	void RegenerateZone(const uint8 aLOD, const bool isInPlaceLODUpdate);
	void UpdateMesh(const uint8 aLOD);

	FVector GetCentrePos();
};
