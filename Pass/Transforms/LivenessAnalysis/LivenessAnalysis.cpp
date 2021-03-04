#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
using namespace llvm;
using namespace std;

#define DEBUG_TYPE "LivenessAnalysis"

using namespace llvm;

namespace {
struct LivenessAnalysis : public FunctionPass {
    string func_name = "test";
    static char ID;
    int CurrentID=1;
    unordered_map<string,set<string> > UEVar;
    unordered_map<string,set<string> > VarKill;
    unordered_map<string,set<string> > LiveOut;
    LivenessAnalysis() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override 
    {
	    if (F.getName() != func_name) return false;
        for (auto& basic_block : F)
        {
            
            set<string> _UEVar;
            set<string> _VarKill;
            set<string> _LiveOut;
            for (auto& inst : basic_block)
            {
                if(inst.getOpcode() == Instruction::Load)
                {
                    string value=inst.getOperand(0)->getName();
                    if(!_VarKill.count(value))
                        _UEVar.insert(value);
                }
                else if(inst.getOpcode() == Instruction::Store)
                {
                    string value =inst.getOperand(1)->getName();
                    _VarKill.insert(value);
                }  
            } // end for inst
            UEVar[basic_block.getName()]=_UEVar;
            VarKill[basic_block.getName()]=_VarKill;
            LiveOut[basic_block.getName()]=_LiveOut;
        }
        bool flag = true;
        while(flag)
        {
            flag = false;
            for (auto& basic_block : F)
            {
                string n = basic_block.getName();
                set<string> _LiveOut;
                set<string> x4;
                for(BasicBlock *Succ : successors(&basic_block))
                {
                    string x = Succ->getName();
                    set<string> x1 = LiveOut[x];
                    set<string> x2 = VarKill[x];
                    set<string> x3 = UEVar[x];
                    set<string> r1;
                    set<string> r2;
                    set_difference(x1.begin(),x1.end(),x2.begin(),x2.end(),inserter(r1,r1.begin()));
                    set_union(r1.begin(),r1.end(),x3.begin(),x3.end(),inserter(r2,r2.begin()));
                    set_union(r2.begin(),r2.end(),x4.begin(),x4.end(),inserter(_LiveOut,_LiveOut.begin()));
                }
                if(LiveOut[n]!=_LiveOut)
                {
                    LiveOut[n]=_LiveOut;
                    flag=true;
                }
            } // end for block
        }
        for (auto& basic_block : F)
        {
            errs()<<"-----"<<basic_block.getName()<<"-----"<<"\n";
            errs()<<"UEVar: ";
            for(auto i:UEVar[basic_block.getName()])
                errs()<<i<<" ";
            errs()<<"\n";

            errs()<<"VarKill: ";
            for(auto i:VarKill[basic_block.getName()])
                errs()<<i<<" ";
            errs()<<"\n";

            errs()<<"LiveOut: ";
            for(auto i:LiveOut[basic_block.getName()])
                errs()<<i<<" ";
            errs()<<"\n";
        }
        return false;
    } // end runOnFunction
}; // end of struct ValueNumbering
}  // end of anonymous namespace

char LivenessAnalysis::ID = 0;
static RegisterPass<LivenessAnalysis> X("LivenessAnalysis", "LivenessAnalysis Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);
