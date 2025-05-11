// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
//#include "LumberjackNPC.h"
//#include "ResourceTree.h"

UTestBTTaskNode::UTestBTTaskNode()
{
    NodeName = "Chop Tree";
}

EBTNodeResult::Type UTestBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    //AAIController* AICon = OwnerComp.GetAIOwner();
    //if (!AICon) return EBTNodeResult::Failed;
    //
    //ALumberjackNPC* NPC = Cast<ALumberjackNPC>(AICon->GetPawn());
    //if (!NPC) return EBTNodeResult::Failed;
    //
    //AResourceTree* Tree = Cast<AResourceTree>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetTree"));
    //if (!Tree || !Tree->CanBeChopped()) return EBTNodeResult::Failed;
    //
    //int32 Amount = Tree->Chop();
    //NPC->AddWood(Amount);

    return EBTNodeResult::Succeeded;
}
