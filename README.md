**Summary:**
The purpose of this project is to make you code a program that solves simple equations.
The program takes a polynomial equation. That is to say, involving only powers, no complicated functions. The program should display its solutions.
Required: Boost v1.67

**Example:**
```
$ ./computor "X^2 - 8 * X + 12 -8 + 12 + 8 * X = -8 + 12 + 8 * X" -v
Polynomial degree: 2
Reduced form: a × X² + b × X + c = 0
		1 × X² -8 × X +12 = 0
a = 1, b = -8, c = 12
Discriminant = (b)² - (4 × a × c) =
		 = (-8)² - (4 × 1 × 12) =
		 = (64) - (48) = 
		 = 16
	-b ± √D
X₁,X₂ = ⎯⎯⎯⎯⎯⎯⎯ =
	2 × a

	8 ± √16
X₁,X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯ =
	2 × 1

	8 ± 4
X₁,X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯
	2

	12
X₁ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯
	2

	4
X₂ = ⎯⎯⎯⎯⎯⎯⎯⎯⎯
	2

Equitation has solution: 
X₁ = 6 and X₂ = 2
```