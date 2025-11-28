library(tidyverse)

read.csv("resultados.csv") |>
ggplot(mapping = aes(x = threads, y = tempo, color = estrategias, group=dimensoes.N.X.N.)) +
        geom_line() +
        geom_point() +
        facet_grid(dimensoes.N.X.N.~estrategias, scales="free_y") +
        labs(
                title = "Desempenho por Número de Threads",
                subtitle = "Comparação entre diferentes estratégias de paralelização",
                x = "Número de Threads",
                y = "Tempo de Execução (segundos)",
                color = "Estratégia"
        ) +
    ylim(0, NA)
