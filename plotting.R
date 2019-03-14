# Graphing the performance of random number generators
library(tidyverse)
library(viridis)
library(ggpubr)
library(plotly)

# Define the output directory
fig_dir = "figures"

if(!dir.exists(fig_dir))
{
  dir.create(fig_dir)
}
perf <- read.csv(file.path("data", "prngs.csv"))
baseline_perf <- max(perf$Time)
perf <- perf %>% mutate(RelPerf = 100*baseline_perf/Time) %>% 
  arrange(RelPerf) %>%                               
  mutate(PRNG = factor(PRNG, PRNG))

p1 <- perf %>% ggplot() +
  geom_bar(aes(x=PRNG, y=RelPerf, fill=PRNG), stat = "identity") + 
  theme_classic() + coord_flip() + 
  scale_fill_viridis("", end=0.95, option="plasma", breaks=rev(perf$PRNG), discrete=TRUE) +
  scale_y_continuous("Performance % (higher is better)") + 
  theme(legend.position = "none")

p2 <- perf %>% ggplot() +
  geom_bar(aes(x=PRNG, y=Time, fill=PRNG), stat = "identity") + 
  theme_classic() + coord_flip() + 
  scale_fill_viridis("", end=0.95, option="plasma", breaks=rev(perf$PRNG), discrete=TRUE) +
  scale_y_continuous("Time taken (s) (lower is better)") + 
  theme(legend.position = "none")

gga <- ggarrange(p1, p2)
pdf(file.path(fig_dir, "prng_perf.pdf"), 8, 4)
print(gga)
dev.off()
ggp <- ggplotly(p1)
ggp2 <- ggplotly(p2)

# Create offline html in the temp dir
htmlwidgets::saveWidget(as_widget(ggp), file.path(normalizePath(fig_dir), "prng_perf1.html"))
htmlwidgets::saveWidget(as_widget(ggp2), file.path(normalizePath(fig_dir), "prng_perf2.html"))
