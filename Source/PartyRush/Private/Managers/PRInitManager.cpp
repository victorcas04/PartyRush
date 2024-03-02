#include "PRInitManager.h"
#include "PRConga.h"
#include "PRCongaInfo.h"
#include "PRGrid.h"
#include "PRMenuManager.h"
#include "PRPlayerController.h"
#include "PRBaseMenuWidget.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "PRGameInstance.h"

void APRInitManager::Init()
{
	// disable input until fully initialized to avoid problems
	APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(IsValid(PController)) DisableInput(PController);

	GI = Cast<UPRGameInstance>(GetGameInstance());
	if (!IsValid(GI)) return;

	if(bIsInGameMap)
	{
		if (OverridedInitRowName == "" || !IsValid(OverridedInitDT))
		{
			InitRowName_Internal = GI->GetInitRowName();
			InitDT_Internal = GI->GetInitDT();
			if (InitRowName_Internal == "" || !IsValid(InitDT_Internal)) return;
		}
		else
		{
			InitRowName_Internal = OverridedInitRowName;
			GI->SetInitRowName(OverridedInitRowName);
			InitDT_Internal = OverridedInitDT;
			GI->SetInitDT(OverridedInitDT);
		}

		FInitData* Row = InitDT_Internal->FindRow<FInitData>(InitRowName_Internal, "APRInitManager::Init");
		if (!Row) return;
		InitData = *Row;

		if(!InitMap())
		{
			// error cannot init map
			return;
		}
		
		if(!InitCongas())
		{
			// error cannot init congas
			return;
		}
		
		if(!InitCamera())
		{
			// error cannot init camera
			return;
		}
	}
	
	if(!InitMapManager())
	{
		// error cannot init menu manager
		return;
	}
	
	if(!InitInput())
	{
		// error cannot init input
		return;
	}
	
	bInitialized = true;
}

void APRInitManager::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

bool APRInitManager::InitMap()
{
	if(!IsValid(InitData.GridSubclass)) return false;

	// create and init grid
	const FName GridName = FName("Grid");
	FActorSpawnParameters SpawnParams{};
	SpawnParams.Owner = this;
	SpawnParams.Name = GridName;

	Map = GetWorld()->SpawnActor<APRGrid>(InitData.GridSubclass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if(!IsValid(Map)) return false;

#if WITH_EDITOR
	Map->SetActorLabel(GridName.ToString());
#endif
	if(!Map->InitGrid(InitData.Size, InitData.ExitPos,
		InitData.FloorCellSubclass, InitData.WallCellSubclass, InitData.ExitCellSubclass)) return false;
	
	Map->SetGIRef(GI);
	Map->SetLevelName(InitRowName_Internal);
	return true;
}

bool APRInitManager::InitCongas()
{
	bool bPlayerExists{false};
	for(int32 i = 0 ; i < InitData.CongasInitData.Num() ; ++i)
	{
		const FCongaData CongaData = InitData.CongasInitData[i];
		if(!IsValid(CongaData.CongaSubclass)) return false;
		
		// create and init conga
		const FName CongaName = FName("Conga" + i);
		FActorSpawnParameters SpawnParams{};
		SpawnParams.Owner = this;
		SpawnParams.Name = CongaName;

		APRConga* NewConga = GetWorld()->SpawnActor<APRConga>(CongaData.CongaSubclass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		if(!IsValid(NewConga)) return false;

		NewConga->CongaMemberChangedLocation_Delegate.AddDynamic(Map, &APRGrid::CellMemberChangedLocation);
#if WITH_EDITOR
		NewConga->SetActorLabel(CongaName.ToString());
#endif
		NewConga->SetMovementTypeAllowed(CongaData.MovementType);
		if(NewConga->InitConga(CongaData.CongaMembersPositions, CongaData.CongaMemberSubclass, i, CongaData.bIsPlayerConga))
		{
			
			if(CongaData.bIsPlayerConga) bPlayerExists = true;
		}
		else
		{
			NewConga->Destroy();
		}
	}
	// there must be at least 1 player conga
	return bPlayerExists;
}

bool APRInitManager::InitCamera() const
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundActors);
	if (FoundActors.Num() <= 0) return false;

	ACameraActor* Camera = Cast<ACameraActor>(FoundActors[0]);
	if(!IsValid(Camera)) return false;

	APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(!IsValid(PController)) return false;
	
	const float CellSize = Map->GetCellSize();
	const float CameraPosVertical =
		-(((InitData.Size.X + 2) / 2) * CellSize) /* center of grid */
		- ((InitData.Size.X % 2 == 0) ? CellSize / 2 : CellSize) /* small offset to center on screen */;
	const float CameraPosHorizontal =
		(((InitData.Size.Y + 2) / 2) * CellSize) /* center of grid */
		- ((InitData.Size.Y % 2 == 0) ? CellSize / 2 : .0f) /* small offset to center on screen */;
	const float CameraHeight = CellSize * FMath::Max(InitData.Size.X + 2, InitData.Size.Y + 2);
	Camera->SetActorLocation(FVector(CameraPosVertical, CameraPosHorizontal, CameraHeight));
	Camera->SetActorRotation(FRotator(-90.0f, .0f, .0f));

	PController->SetViewTargetWithBlend(Camera);
	
	return true;
}

bool APRInitManager::InitMapManager()
{
	if(!IsValid(GI->GetMenuManagerClass())) return false;
	// create and init grid
	const FName MenuManagerName = FName("MenuManager");
	FActorSpawnParameters SpawnParams{};
	SpawnParams.Owner = this;
	SpawnParams.Name = MenuManagerName;

	MenuManagerRef = GetWorld()->SpawnActor<APRMenuManager>(GI->GetMenuManagerClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if(!IsValid(MenuManagerRef)) return false;

	MenuManagerRef->Init(InitMenuClass);
	GI->OnLevelGameOver.AddDynamic(MenuManagerRef, &APRMenuManager::LevelGameOver);
	GI->OnLevelWin.AddDynamic(MenuManagerRef, &APRMenuManager::LevelWin);
	
	return true;
}

bool APRInitManager::InitInput()
{
	APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(!IsValid(PController)) return false;

	if(APRPlayerController* PRPController = Cast<APRPlayerController>(PController))
	{
		PRPController->Init(Map, MenuManagerRef);
	}
	else
	{
		return false;
	}
	EnableInput(PController);
	
	return true;
}

