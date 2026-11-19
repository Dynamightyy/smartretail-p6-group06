# smartretail-p6-group06
### Thu Hoài — Member 2, KPI and Date Processing
For M1, I am responsible for drawing the team's main flowchart for generating alerts for a single day. The flowchart shows how the program checks for stockouts, a low conversion rate, and revenue below target. It also shows how the program sorts alerts by priority and creates a proposed action with `PENDING` status for each alert. I work with LyLy to check that the flowchart matches the pseudocode before it is added to the team's M1 setup pull request.

For M2, I implement the calculation of two daily KPIs. The conversion rate is calculated by dividing the number of orders by the number of visitors. Target achievement is calculated by dividing actual revenue by the revenue target. Both are expressed as percentages. If there are zero visitors on a given day, the program displays the conversion rate as `n/a`. I prepare a flowchart and pseudocode for the KPI calculation and submits them with the code in her first pull request.

For M3, I implement the logic for finding the requested date and the most recent earlier date with available data for the same store. If the user leaves the date blank, the program selects the latest date with available data. When both days have the values needed for comparison, the program calculates how much each KPI increased or decreased in percentage points. The code, flowchart, and pseudocode are submitted together in her second pull request.

My planned testing work includes checking the KPI calculations against the sample data, testing days with zero visitors, and checking how the program handles gaps between dates. She will record the expected and actual results in the team's test case file.

So far, I have drawn the team's main flowchart, cloned the repository, opened the project in VS Code, updated her local `main` branch, and created a separate branch for the KPI work. I have also checked the Pull requests page and compared `branch-1` with `main` to see whether any changes were ready for the M1 setup pull request.
### Bích Thủy - Member 3, Alert Engine
For M1,
