# SmartRetail P6 - Store Intelligence & Alert Engine
## Team members and instructor

- Course: Fundamentals of Programming (C++)
- Project: P6 - Store Intelligence & Alert Engine
- Group: 06

| Member | GitHub username | Main responsibility |
| --- | --- | --- |
| Lưu Thị Ly Ly | Dynamightyy | Team leader; data input and validation |
| Trương Phạm Thu Hoài | Hoaitruong-29 | KPI and date processing; core flowchart; README |
| Đỗ Bích Thủy | boa-pooper | Alert generation, severity sorting and proposed actions |
| Nguyễn Thanh Thảo | boa-pooper | Trend, summary and report formatting |

Instructor: Lê Văn Thể 
Instructor's GitHub account: [@vvvanthe](https://github.com/vvvanthe)

## Problem specification

This C++17 console program reads daily store metrics, calculates KPIs,
compares the selected day with the previous available day, generates
alerts and proposes actions for a manager to review.

The following sections describe the required program behaviour.
Implementation is in progress; the build/run commands must be verified
after the source code and datasets are added.

### Input

The program reads one CSV file:

`<data_folder>/daily_store.csv`

Required header:

```csv
date,store_id,visitors,orders,revenue,target_revenue,stockout_products
```

- `date`: a valid date in YYYY-MM-DD format.
- `store_id`: the store identifier.
- `visitors`, `orders`, `stockout_products`: non-negative integers.
- `revenue`, `target_revenue`: integer amounts in VND.
- `target_revenue` must be greater than zero.

Command-line format:

```text
p6 <data_folder> [store_id] [date]
```

The default store is `S001`. If no date is supplied, the program uses
the latest available date for the selected store.

### Processing

1. Read CSV records into a vector of structs.
2. Validate each record. Skip invalid rows and print a warning to
   standard error (`cerr`) with the line number.
3. Select the requested store and date.
4. Calculate the KPIs:
   - Conversion rate = orders / visitors × 100%.
   - Target achievement = revenue / target_revenue × 100%.
   - If visitors = 0, conversion is `n/a`; do not divide by zero.
5. Find the most recent earlier date with data for the same store.
   Compare the KPIs using percentage-point changes.
6. Check all three alert rules independently, in the order below.

| Order | Condition | Severity | Alert | Proposed action |
| --- | --- | --- | --- | --- |
| 1 | stockout_products > 3 | HIGH | Inventory Issue | Check and restock shelves |
| 2 | Valid conversion rate < 20% | HIGH | Low Conversion | Review customer engagement |
| 3 | Target achievement < 80% | MEDIUM | Sales Below Target | Add staff support |

7. Sort alerts using a manually implemented stable bubble sort:
   HIGH before MEDIUM; equal-severity alerts retain their rule order.
8. Create one proposed action per alert, initially marked `PENDING`.
9. Calculate the trend and summary for all available dates of the
   selected store.

If a file is missing, the dataset is empty, or the requested store/date
has no data, display a clear error without crashing.

### Output

The program prints:

- A daily report containing store/date, visitors, orders, revenue,
  conversion rate, target achievement and stockouts.
- A comparison with the previous available date, if one exists.
- Alerts in the required severity and rule order.
- Recommended actions and their `PENDING` approval status.
- A TREND table for all available dates of the selected store,
  including conversion, target achievement, stockouts and alert codes.
- A SUMMARY containing:
  - Number of days with at least one HIGH alert out of all available days.
  - Date with the lowest valid conversion rate, excluding `n/a` days.
  - Longest sequence of available dates where every date has an alert;
    report its length, start date and end date. On a tie, use the
    earliest sequence.

Rates are displayed using `fixed` and `setprecision(2)`.

## Build and run

Prerequisite: a compiler supporting C++17, such as g++.

Run the following commands from the repository root.

### macOS, Linux or Git Bash

```bash
mkdir -p bin
g++ -std=c++17 -Wall -Wextra src/main.cpp -o bin/p6

# Sample case from the project brief
./bin/p6 data/sample S001 2026-08-21

# Use the default store and its latest available date
./bin/p6 data/sample

# Other lecturer-provided datasets
./bin/p6 data/full
./bin/p6 data/edge/empty
./bin/p6 data/edge/dirty
```

### Windows PowerShell

```powershell
New-Item -ItemType Directory -Force bin | Out-Null
g++ -std=c++17 -Wall -Wextra src/main.cpp -o bin/p6.exe

.\bin\p6.exe data/sample S001 2026-08-21
.\bin\p6.exe data/sample
.\bin\p6.exe data/full
.\bin\p6.exe data/edge/empty
.\bin\p6.exe data/edge/dirty
```

The executable is generated locally in `bin/` and is not committed
to the repository.

## Assumptions and limitations

- The CSV file has a header on its first line; fields contain no commas.
- Store records may be interleaved, and dates may have gaps.
- Valid dates use YYYY-MM-DD format and can be compared as strings.
- Revenue values are stored using `long long`; ratios use floating-point
  calculations.
- A day with zero visitors is valid, but its conversion rate is `n/a`.
  It does not trigger Low Conversion and is excluded from the search
  for the lowest conversion.
- A row with zero target revenue is invalid and must be skipped with
  a warning.
- The previous day means the previous available date for the same store,
  rather than necessarily the previous calendar date.
- Alert streaks count consecutive available records in date order;
  a missing calendar date does not by itself break a streak.
- Lecturer-provided input datasets are kept unchanged.

## Project boundaries

- The mandatory program proposes actions with status `PENDING`.
  It never automatically marks an action as `APPROVED`.
- The program does not calculate replenishment or order quantities.
- P6 reads `daily_store.csv`; it does not use the CSV files belonging
  to the other SmartRetail projects.
- The implementation follows the required course techniques:
  functions, structs, vectors, strings, file input, manually written
  searching/sorting algorithms and at least one recursive function.
- Alert sorting uses stable bubble sort, not `std::sort`.

## References

- Lecturer-provided Project Brief P6:
  Store Intelligence & Alert Engine, especially sections 3-7.
- Lecturer-provided submission guide, especially section 6:
  required README contents.
- Lecturer-provided GitHub workflow guide.
## Task assignment table
This plan follows our team's agreed areas of responsibility.
Function names, reviewers and supporting documentation tasks are proposed and will be agreed during review.
All C++ functions and structs will be implemented in 'src/main.cpp'.
Core function: 'evaluateDay ()' - T10 - Bích Thủy.
| ID | Task | Function / file | Assignee | Reviewer | Flowchart | PR |
| --- | --- | --- | --- | --- | --- | --- |
| T01 | Set up public repository, invite collaborators and protect main | GitHub repository settings | Ly Ly | N/A | Not needed | N/A |
| T02 | Create repository skeleton, PR template and copy lecturer data | `.gitignore`, `.github/pull_request_template.md`, `src/`, `data/`, `tests/`, `docs/` | Ly Ly | Thu Hoài | Not needed | Pending |
| T03 | Create task assignment table | `README.md` | Thu Hoài | Ly Ly | Not needed | #7 |
| T04 | Define shared structs and read daily_store.csv into a vector | Shared structs, `loadDailyStore()` | Ly Ly | Thu Hoài | Required | Pending |
| T05 | Validate CSV records, skip invalid rows and print warnings with line numbers | `isValidDate()`, `validateRecord()` | Ly Ly | Thanh Thảo | Required | Pending |
| T06 | Calculate conversion and target achievement; handle zero denominators | `calculateKPI()` | Thu Hoài | Bích Thủy | Required | Pending |
| T07 | Filter store records, sort dates, recursively find the selected date and locate the previous available date | `filterStoreDays()`, `sortDaysByDate()`, `findDay()`, `previousDay()` | Thu Hoài | Ly Ly | Required | Pending |
| T08 | Compare the selected day with the previous available day | `compareDays()` | Thu Hoài | Thanh Thảo | Required | Pending |
| T09 | Check inventory, conversion and target alert rules | `checkInventory()`, `checkConversion()`, `checkTarget()` | Bích Thủy | Thu Hoài | Required | Pending |
| T10 | CORE: generate daily alerts and sort by severity using stable bubble sort | `evaluateDay()`, `sortAlerts()` | Bích Thủy | Ly Ly | Required | Pending |
| T11 | Create one proposed action per alert with PENDING status | `createProposedActions()` | Bích Thủy | Thanh Thảo | Required | Pending |
| T12 | Print the daily KPI report, alerts and proposed actions | `printReport()` | Thanh Thảo | Thu Hoài | Required | Pending |
| T13 | Print the TREND table for every available day of the selected store | `printTrend()` | Thanh Thảo | Bích Thủy | Required | Pending |
| T14 | Calculate and print HIGH-alert days, lowest conversion and longest alert streak | `calculateSummary()`, `printSummary()` | Thanh Thảo | Ly Ly | Required | Pending |
| T15 | Handle command-line arguments, defaults, errors and the overall program flow | `main()` | Ly Ly | Thanh Thảo | Required | Pending |
| T16 | Document overall flow, function relationships, structs, input/output and algorithms | `docs/architecture.md` | Ly Ly | Thanh Thảo | Not needed | Pending |
| T17 | Write TC01–TC07 and their expected outputs | `tests/test_cases.md`, `tests/expected/` | Bích Thủy | Thu Hoài | Not needed | Pending |
| T18 | Run tests on sample, full and edge data; record actual results and Pass/Fail | `tests/test_cases.md` | Thanh Thảo | Bích Thủy | Not needed | Pending |
| T19 | Prepare presentation slides and the live demo plan | `docs/slides.pdf` | Thanh Thảo | Bích Thủy | Not needed | Pending |
| T20 | Complete README specification, build/run instructions, assumptions, references and AI declaration | `README.md` | Thu Hoài | Ly Ly | Not needed | Pending |
| T21 | Check the final submission and push the final tag | Git tag `final` on `main` | Ly Ly | N/A | Not needed | N/A |
| T22 | Draw the main project flowchart | `docs/flowcharts/` | Thu Hoài | Ly Ly | Required | Pending |

Notes:

- `Required` means a flowchart and pseudocode must accompany the code task;
  it does not mean those documents are already complete.
- Each code task must include `docs/flowcharts/Txx-task-name.md`,
  containing its flowchart image and pseudocode.
- `Pending` must be replaced with the actual PR number or link.
- `N/A` identifies repository settings or tagging work that does not use a PR.
- Reviewers must be different from assignees.
- Each member must author at least two merged code PRs and one merged
  non-code PR, and review at least two PRs from other members.

## AI declaration

ChatGPT was used to assist in formatting our existing task distribution into a structured assignment table and suggesting initial naming conventions. All task scopes, function designs, and reviewer assignments were reviewed, adjusted, and finalized by the team, with each member independently implementing their assigned components.
