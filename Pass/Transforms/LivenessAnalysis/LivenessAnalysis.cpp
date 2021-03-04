#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include <string>
#include <unordered_map>
using namespace llvm;
using namespace std;

#define DEBUG_TYPE "LivenessAnalysis"

using namespace llvm;

namespace {
struct LivenessAnalysis : public FunctionPass {
    string func_name = "test";
    static char ID;
    unordered_map<Value *,int> V_MAP;
    unordered_map<string, int> OP_MAP;
    int CurrentID=1;
    LivenessAnalysis() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
	    
        errs() << "LivenessAnalysis: " << F.getName() << "\n";
        if (F.getName() != func_name) return false;

        for (auto& basic_block : F)
        {
            for (auto& inst : basic_block)
            {
                //errs() << inst << "\n";
                if(inst.getOpcode() == Instruction::Load){
                    errs() << formatv("{0,-40}", inst); 
                    auto args1=inst.getOperand(0);
                  
                    int id= V_MAP[args1];
                    errs() << "\t" <<id<<"="<<id<< "\n";
                    V_MAP[&inst]=id;
                }
                if(inst.getOpcode() == Instruction::Store){
                    errs() << formatv("{0,-40}", inst); 
                    auto args1=inst.getOperand(0);
                    auto args2=inst.getOperand(1);
                    int id = 0;
                    if(V_MAP.count(args1)==0)
                    {                       
                        V_MAP[args1]=CurrentID;
                        V_MAP[args2]=CurrentID;
                        errs() << "\t" <<CurrentID<<"="<<CurrentID<< "\n";
                        CurrentID++;
                    }
                    else
                    {
                        id = V_MAP[args1];
                        V_MAP[args2]=id;
                        errs() << "\t" <<id<<"="<<id<< "\n";
                    }
                 
                    //errs() << "This is Store"<<"\n";
                }
                if (inst.isBinaryOp())
                {
                    errs() << formatv("{0,-40}", inst);
                    string op;
                    // errs() << "Op Code:" << inst.getOpcodeName()<<"\n";
                    if(inst.getOpcode() == Instruction::Add){
                        op ="+";
                    }
                    if(inst.getOpcode() == Instruction::Sub){
                        op ="-";
                    }
                    if(inst.getOpcode() == Instruction::Mul){
                        op = "*";
                    }
                    if(inst.getOpcode() == Instruction::SDiv){
                        op = "/";
                    }
                    int v1;
                    int v2;
                    auto args1=inst.getOperand(0);
                    auto args2=inst.getOperand(1);
                    if(V_MAP.count(args1)==0)
                    {
                        V_MAP[args1]=CurrentID;
                        v1 = CurrentID++;
                    }   
                    else    v1 = V_MAP[args1];
                    if(V_MAP.count(args2)==0)
                    {
                        V_MAP[args2]=CurrentID;
                        v2 = CurrentID ++;
                    } 
                    else   v2 = V_MAP[args2];
                    string v = to_string(v1)+op+to_string(v2);
                    if(OP_MAP.count(v)==0)
                    {
                        OP_MAP[v]=CurrentID;
                        V_MAP[&inst]=CurrentID;
                        errs()<<"\t"<<CurrentID<<"="<<v1<<op<<v2<< "\n";
                        CurrentID++;
                    }
                    else
                    {
                        int temp = OP_MAP[v];
                        V_MAP[&inst]=temp;
                        errs()<<"\t"<<temp<<"="<<v1<<op<<v2<<"Redundant"<<"\n";
                    }
                        //errs() << "\t" <<  *(*it) << "\n";  
                    
                    // end if
                }
                
            } // end for inst
        } // end for block
        return false;
    } // end runOnFunction
}; // end of struct ValueNumbering
}  // end of anonymous namespace

char LivenessAnalysis::ID = 0;
static RegisterPass<LivenessAnalysis> X("LivenessAnalysis", "LivenessAnalysis Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);
