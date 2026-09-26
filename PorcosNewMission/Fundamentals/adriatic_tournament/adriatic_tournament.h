#ifndef ADRIATIC_TOURNAMENT_H
#define ADRIATIC_TOURNAMENT_H

struct PilotResult
{
    char name[64];
    int score;
    struct PilotResult *next;
};

void simulate_pilot(const char *pilot_name);
struct PilotResult *load_tournament_results(char **pilots_names);
struct PilotResult *sort_results_by_score(struct PilotResult *head);
void print_tournament_ranking(const struct PilotResult *head);
void destroy_results(struct PilotResult *head);
void run_adriatic_tournament(char **pilots_names);

#endif // !ADRIATIC_TOURNAMENT_H
