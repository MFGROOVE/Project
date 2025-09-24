library(tidyverse)

csv <- read.csv("resultados.csv")
plot_1000 <- csv |>
        filter(dimensoes.N.X.N. == 1000)
ggplot(data = plot_1000, mapping = aes(x = threads, y = tempo, color = estrategias)) +
        geom_line() +
        geom_point() +
        facet_wrap(~estrategias, nrow = 2) +
        labs(
                title = "Desempenho por Número de Threads (Matriz 1000x1000)",
                subtitle = "Comparação entre diferentes estratégias de paralelização",
                x = "Número de Threads",
                y = "Tempo de Execução (segundos)",
                color = "Estratégia"
        )

plot_100 <- csv |>
        filter(dimensoes.N.X.N. == 100)
ggplot(data = plot_100, mapping = aes(x = threads, y = tempo, color = estrategias)) +
        geom_line() +
        geom_point() +
        facet_wrap(~estrategias, nrow = 2) +
        labs(
                title = "Desempenho por Número de Threads (Matriz 100x100)",
                subtitle = "Comparação entre diferentes estratégias de paralelização",
                x = "Número de Threads",
                y = "Tempo de Execução (segundos)",
                color = "Estratégia"
        )

plot_10 <- csv |>
        filter(dimensoes.N.X.N. == 10)
ggplot(data = plot_10, mapping = aes(x = threads, y = tempo, color = estrategias)) +
        geom_line() +
        geom_point() +
        facet_wrap(~estrategias, nrow = 2) +
        labs(
                title = "Desempenho por Número de Threads (Matriz 10x10)",
                subtitle = "Comparação entre diferentes estratégias de paralelização",
                x = "Número de Threads",
                y = "Tempo de Execução (segundos)",
                color = "Estratégia"
        )
