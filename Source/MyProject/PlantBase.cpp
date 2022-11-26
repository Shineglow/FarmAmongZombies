// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantBase.h"
#include <ProceduralMeshComponent.h>
#include <Kismet/KismetMathLibrary.h>

void APlantBase::CreateOptimizedMesh() {
	float UV_Scaler_X = PlantFieldSize.X / PlantFieldSize.Y;

	for ( int y = 0; y < PlantFieldSize.Y; y++ )
		for ( int x = 0; x < PlantFieldSize.X; x++ ) {
			FVector2D xyPos = FVector2D(x, y);
			FVector2D NormalPos = FVector2D(x / PlantFieldSize.X * step * UV_Scaler_X,
					(PlantFieldSize.Y - y) / PlantFieldSize.Y * step);
			float Heigth = FMath::PerlinNoise2D(NormalPos);
			Vertices.Add(FVector(xyPos * step, Heigth * 20));
			
			UVs.Add(NormalPos);
		}

	for ( int y = 0; y < PlantFieldSize.Y - 1; y++ )
		for ( int x = 0; x < PlantFieldSize.X - 1; x++ )
			AddQuad(x, y);
	
	ProcMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), 
								UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), true);

	if ( Material ) {
		ProcMesh->SetMaterial(0, Material);
	}
}

void APlantBase::AddQuad(int x, int y) {
	int topLeft = x + PlantFieldSize.X * y;
	int botLeft = x + PlantFieldSize.X * (y + 1);

	Triangles.Add(topLeft);
	Triangles.Add(botLeft);
	Triangles.Add(botLeft+1);// bot right

	Triangles.Add(topLeft);
	Triangles.Add(botLeft+1);// bot left
	Triangles.Add(topLeft+1);// top right
}

// Sets default values
APlantBase::APlantBase() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	ProcMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APlantBase::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void APlantBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

