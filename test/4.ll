; ModuleID = '4.c'
source_filename = "4.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.12.0"

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @test() #0 {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  %e = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 5, i32* %b, align 4
  store i32 5, i32* %a, align 4
  store i32 0, i32* %c, align 4
  store i32 4, i32* %e, align 4
  store i32 4, i32* %d, align 4
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4
  %cmp = icmp slt i32 %0, 100
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %1 = load i32, i32* %a, align 4
  %2 = load i32, i32* %b, align 4
  %sub = sub nsw i32 %1, %2
  store i32 %sub, i32* %c, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %for.body
  %3 = load i32, i32* %i, align 4
  %4 = load i32, i32* %e, align 4
  %add = add nsw i32 %3, %4
  %cmp1 = icmp slt i32 %add, 20
  br i1 %cmp1, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %5 = load i32, i32* %a, align 4
  %6 = load i32, i32* %i, align 4
  %add2 = add nsw i32 %5, %6
  store i32 %add2, i32* %i, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %7 = load i32, i32* %c, align 4
  %8 = load i32, i32* %a, align 4
  %mul = mul nsw i32 %7, %8
  store i32 %mul, i32* %b, align 4
  br label %for.inc

for.inc:                                          ; preds = %while.end
  %9 = load i32, i32* %i, align 4
  %inc = add nsw i32 %9, 1
  store i32 %inc, i32* %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret void
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 8.0.0 (trunk 350498)"}
