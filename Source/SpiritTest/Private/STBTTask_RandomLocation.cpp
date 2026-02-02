#include "STBTTask_RandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

USTBTTask_RandomLocation::USTBTTask_RandomLocation()
{
	NodeName = "Find Random Location";
}

EBTNodeResult::Type USTBTTask_RandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<UBlackboardComponent> Blackboard = OwnerComp.GetBlackboardComponent();

	if (!Blackboard)
	{
		return EBTNodeResult::Failed;
	}

	const FVector OriginLocation = Blackboard->GetValueAsVector(OriginLocationKey.SelectedKeyName);
	if (OriginLocation == FAISystem::InvalidLocation)
	{
		return EBTNodeResult::Failed;
	}

	const UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation ResultLocation;
	const bool bFound = NavSystem->GetRandomReachablePointInRadius(OriginLocation, SearchRadius, ResultLocation);

	if (bFound)
	{
		Blackboard->SetValueAsVector(ResultLocationKey.SelectedKeyName, ResultLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

FString USTBTTask_RandomLocation::GetStaticDescription() const
{
	return FString::Format(TEXT("Find random point in radius {0} around {1}"), {
		                       SearchRadius.ToString(),
		                       OriginLocationKey.SelectedKeyName.ToString()
	                       });
}
