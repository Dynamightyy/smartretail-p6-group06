
# SmartRetail P6 - Group 06

## 1. Project Information

Course: Fundamentals of Programming (C++)

Project: P6 - Store Intelligence & Alert Engine

Programming Language: C++17

## 2. Project Description

This project develops a C++ program to analyze
daily store performance.

The final program will:
- Read daily store data from a CSV file.
- Validate input data.
- Calculate Conversion Rate.
- Calculate Target Achievement.
- Compare results with the previous available day.
- Generate alerts based on predefined rules.
- Recommend actions with PENDING approval status.
- Display TREND and SUMMARY reports.

## 3. Project Structure

- src/: C++ source code
- data/: Input datasets
- tests/: Test cases and expected outputs
- docs/: Architecture, pseudocode and flowcharts
- .github/: Pull Request template

## 4. Build Instructions

Requirements:
- A C++17 compiler (g++)

Compile:

g++ -std=c++17 -Wall -Wextra src/main.cpp -o p6.exe

## 5. Run Instructions

Example:

./p6.exe data/sample S001 2026-08-21

Command format:

p6 <data_folder> [store_id] [date]

Default store_id: S001

Default date: latest available date for the store.

Note: The program is currently in the setup stage.
Data processing and reporting are not implemented yet.

## 6. Task Assignment

| Member | Responsibility |
|---|---|
| Member 1 - Leader | Data Input & Validation |
| Member 2 | KPI & Date Processing |
| Member 3 | Alert Engine |
| Member 4 | Trend, Summary & Report |

All members are responsible for their own code,
pseudocode, flowcharts, and testing.

## 7. Testing

Required test cases: TC01 - TC07.

Test details and results will be documented
in tests/test_cases.md.

## 8. GitHub Workflow

1. Update the local main branch.
2. Create a feature branch.
3. Implement and test the assigned task.
4. Commit changes.
5. Push the feature branch.
6. Create a Pull Request.
7. Request review from another team member.
8. Merge after approval.

## 9. AI Declaration

The team will document any AI tools used,
their purposes, and how the generated content
was reviewed and verified.

## 10. Project Status

Initial repository setup in progress.
