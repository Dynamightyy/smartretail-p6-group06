# SmartRetail P6 - Store Intelligence & Alert Engine
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
