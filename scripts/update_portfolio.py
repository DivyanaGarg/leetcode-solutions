import os
import re
import json
import time
import requests
from collections import Counter
from pathlib import Path


# ============================================================
# CONFIGURATION
# ============================================================

README_FILE = Path("README.md")

LEETCODE_GRAPHQL = "https://leetcode.com/graphql"

SUPPORTED_EXTENSIONS = {
    ".java": "Java",
    ".cpp": "C++",
    ".py": "Python",
    ".js": "JavaScript",
    ".ts": "TypeScript",
    ".c": "C",
    ".cs": "C#",
    ".go": "Go",
    ".rs": "Rust",
}


# ============================================================
# LEETCODE API
# ============================================================

QUERY = """
query problemsetQuestionList(
    $categorySlug: String
    $limit: Int
    $skip: Int
    $filters: QuestionListFilterInput
) {
    problemsetQuestionList: questionList(
        categorySlug: $categorySlug
        limit: $limit
        skip: $skip
        filters: $filters
    ) {
        total: totalNum

        questions: data {
            questionFrontendId
            title
            titleSlug
            difficulty

            topicTags {
                name
                slug
            }
        }
    }
}
"""


def fetch_all_problems():

    print("Fetching LeetCode problem metadata...")

    problems = {}

    skip = 0
    limit = 100

    while True:

        variables = {
            "categorySlug": "",
            "skip": skip,
            "limit": limit,
            "filters": {}
        }

        payload = {
            "query": QUERY,
            "variables": variables,
            "operationName": "problemsetQuestionList"
        }

        try:

            response = requests.post(
                LEETCODE_GRAPHQL,
                json=payload,
                timeout=30
            )

            response.raise_for_status()

            data = response.json()

            result = (
                data
                .get("data", {})
                .get("problemsetQuestionList")
            )

            if not result:
                print("Could not read LeetCode response.")
                break

            questions = result.get("questions", [])

            if not questions:
                break

            for question in questions:

                problem_id = str(
                    question["questionFrontendId"]
                )

                problems[problem_id] = {
                    "id": problem_id,
                    "title": question["title"],
                    "slug": question["titleSlug"],
                    "difficulty": question["difficulty"],
                    "topics": [
                        tag["name"]
                        for tag in question.get(
                            "topicTags",
                            []
                        )
                    ]
                }

            print(
                f"Fetched {len(problems)} problems..."
            )

            if len(questions) < limit:
                break

            skip += limit

            # Small delay to avoid hammering the endpoint.
            time.sleep(0.5)

        except Exception as error:

            print(
                f"Error fetching LeetCode data: {error}"
            )

            break

    print(
        f"Finished. Metadata available for "
        f"{len(problems)} problems."
    )

    return problems


# ============================================================
# FIND LEETCODE SOLUTIONS
# ============================================================

def find_solutions():

    solutions = []

    ignored_directories = {
        ".git",
        ".github",
        "scripts",
        "__pycache__"
    }

    for root, directories, files in os.walk("."):

        directories[:] = [
            directory
            for directory in directories
            if directory not in ignored_directories
        ]

        for file in files:

            extension = Path(file).suffix.lower()

            if extension not in SUPPORTED_EXTENSIONS:
                continue

            full_path = Path(root) / file

            relative_path = full_path.as_posix()

            # Look for a LeetCode problem number.
            #
            # Examples:
            # 0001-two-sum
            # 1-two-sum
            # 704-binary-search

            match = re.search(
                r"(?:^|/)(\d{1,4})[-_]",
                relative_path
            )

            if not match:
                continue

            problem_id = str(
                int(match.group(1))
            )

            language = SUPPORTED_EXTENSIONS[
                extension
            ]

            solutions.append({
                "id": problem_id,
                "file": relative_path,
                "language": language
            })

    return solutions


# ============================================================
# MERGE SOLUTIONS WITH LEETCODE METADATA
# ============================================================

def build_problem_list(
    solutions,
    metadata
):

    problems = {}

    for solution in solutions:

        problem_id = solution["id"]

        if problem_id not in metadata:

            print(
                f"Warning: no metadata for "
                f"problem {problem_id}"
            )

            continue

        info = metadata[problem_id]

        if problem_id not in problems:

            problems[problem_id] = {
                "id": problem_id,
                "title": info["title"],
                "slug": info["slug"],
                "difficulty": info["difficulty"],
                "topics": info["topics"],
                "languages": set(),
                "files": []
            }

        problems[problem_id][
            "languages"
        ].add(solution["language"])

        problems[problem_id][
            "files"
        ].append(solution["file"])

    return list(problems.values())


# ============================================================
# FORMAT HELPERS
# ============================================================

def difficulty_badge(difficulty):

    if difficulty == "Easy":
        return "🟢 Easy"

    if difficulty == "Medium":
        return "🟡 Medium"

    if difficulty == "Hard":
        return "🔴 Hard"

    return difficulty


def topic_key(topic):

    topic = topic.lower()

    aliases = {
        "array": "Arrays",
        "binary search": "Binary Search",
        "string": "Strings",
        "recursion": "Recursion",
        "linked list": "Linked List",
        "stack": "Stack",
        "queue": "Queue",
        "tree": "Trees",
        "graph": "Graphs",
        "dynamic programming": "Dynamic Programming",
    }

    return aliases.get(
        topic,
        topic.title()
    )


# ============================================================
# README STATISTICS
# ============================================================

def generate_statistics(problems):

    difficulties = Counter(
        problem["difficulty"]
        for problem in problems
    )

    languages = Counter()

    topics = Counter()

    for problem in problems:

        for language in problem["languages"]:
            languages[language] += 1

        for topic in problem["topics"]:
            topics[topic_key(topic)] += 1

    return (
        difficulties,
        languages,
        topics
    )


# ============================================================
# GENERATE PROBLEM TABLE
# ============================================================

def generate_problem_table(problems):

    problems.sort(
        key=lambda problem:
        int(problem["id"])
    )

    lines = []

    lines.append(
        "| # | Problem | Difficulty | Topics | Language |"
    )

    lines.append(
        "|---:|:---|:---|:---|:---|"
    )

    for problem in problems:

        number = problem["id"]

        title = problem["title"]

        slug = problem["slug"]

        difficulty = difficulty_badge(
            problem["difficulty"]
        )

        topics = ", ".join(
            problem["topics"]
        )

        languages = ", ".join(
            sorted(problem["languages"])
        )

        url = (
            f"https://leetcode.com/problems/"
            f"{slug}/"
        )

        lines.append(
            f"| {number} "
            f"| [{title}]({url}) "
            f"| {difficulty} "
            f"| {topics} "
            f"| {languages} |"
        )

    return "\n".join(lines)


# ============================================================
# GENERATE TOPIC TABLE
# ============================================================

def generate_topic_table(topics):

    preferred_order = [
        "Arrays",
        "Binary Search",
        "Strings",
        "Recursion",
        "Linked List",
        "Stack",
        "Queue",
        "Trees",
        "Graphs",
        "Dynamic Programming"
    ]

    lines = [
        "| Topic | Problems |",
        "|:---|---:|"
    ]

    for topic in preferred_order:

        lines.append(
            f"| {topic} | "
            f"{topics.get(topic, 0)} |"
        )

    return "\n".join(lines)


# ============================================================
# GENERATE LANGUAGE TABLE
# ============================================================

def generate_language_table(languages):

    preferred_order = [
        "Java",
        "C++",
        "Python",
        "JavaScript",
        "TypeScript",
        "C",
        "C#",
        "Go",
        "Rust"
    ]

    lines = [
        "| Language | Problems |",
        "|:---|---:|"
    ]

    for language in preferred_order:

        if languages.get(language, 0) > 0:

            lines.append(
                f"| {language} | "
                f"{languages[language]} |"
            )

    return "\n".join(lines)


# ============================================================
# UPDATE README
# ============================================================

def update_readme(problems):

    if not README_FILE.exists():

        print("README.md does not exist.")

        return

    difficulties, languages, topics = (
        generate_statistics(problems)
    )

    total = len(problems)

    easy = difficulties.get(
        "Easy",
        0
    )

    medium = difficulties.get(
        "Medium",
        0
    )

    hard = difficulties.get(
        "Hard",
        0
    )

    language_table = (
        generate_language_table(
            languages
        )
    )

    topic_table = (
        generate_topic_table(
            topics
        )
    )

    problem_table = (
        generate_problem_table(
            problems
        )
    )

    with open(
        README_FILE,
        "r",
        encoding="utf-8"
    ) as file:

        readme = file.read()

    # --------------------------------------------------------
    # Progress table
    # --------------------------------------------------------

    progress_pattern = re.compile(
        r"## 📊 Progress.*?"
        r"(?=## 💻 Languages)",
        re.S
    )

    progress = f"""## 📊 Progress

| 🟢 Easy | 🟡 Medium | 🔴 Hard | 🧠 Total |
|:---:|:---:|:---:|:---:|
| {easy} | {medium} | {hard} | {total} |

"""

    readme = progress_pattern.sub(
        progress,
        readme
    )

    # --------------------------------------------------------
    # Languages
    # --------------------------------------------------------

    language_pattern = re.compile(
        r"## 💻 Languages.*?"
        r"(?=## 🧠 Topics)",
        re.S
    )

    language_section = (
        "## 💻 Languages\n\n"
        + language_table
        + "\n\n"
    )

    readme = language_pattern.sub(
        language_section,
        readme
    )

    # --------------------------------------------------------
    # Topics
    # --------------------------------------------------------

    topic_pattern = re.compile(
        r"## 🧠 Topics.*?"
        r"(?=## 📚 Problems)",
        re.S
    )

    topic_section = (
        "## 🧠 Topics\n\n"
        + topic_table
        + "\n\n"
    )

    readme = topic_pattern.sub(
        topic_section,
        readme
    )

    # --------------------------------------------------------
    # Problems
    # --------------------------------------------------------

    problem_pattern = re.compile(
        r"<!-- PROBLEMS_START -->.*?"
        r"<!-- PROBLEMS_END -->",
        re.S
    )

    problem_section = (
        "<!-- PROBLEMS_START -->\n\n"
        + problem_table
        + "\n\n"
        + "<!-- PROBLEMS_END -->"
    )

    readme = problem_pattern.sub(
        problem_section,
        readme
    )

    with open(
        README_FILE,
        "w",
        encoding="utf-8"
    ) as file:

        file.write(readme)

    print(
        f"README updated. "
        f"{total} problems found."
    )


# ============================================================
# MAIN
# ============================================================

def main():

    print()
    print(
        "========================================"
    )
    print(
        "      LEETCODE PORTFOLIO BUILDER"
    )
    print(
        "========================================"
    )
    print()

    metadata = fetch_all_problems()

    solutions = find_solutions()

    print(
        f"Found {len(solutions)} solution files."
    )

    problems = build_problem_list(
        solutions,
        metadata
    )

    update_readme(problems)

    print()
    print("Done!")
    print()


if __name__ == "__main__":
    main()
