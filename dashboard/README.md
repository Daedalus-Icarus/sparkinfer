# sparkinfer dashboard

Static, self-contained status page — current **frontier**, the **optimization journey**, **vs
llama.cpp**, **emission weights**, the **auto-eval labels**, and **evaluated PRs**. Styled in the
org's template identity (purple `#7B5DFF` / lime `#D4FF12`, Sora + Work Sans). No build step, no
framework — just `index.html` + `data.js`.

## View
Open `dashboard/index.html` in a browser (it loads `dashboard/data.js`).

## Update the data
Everything is driven by `window.SPARKINFER` in **`data.js`**:
- `status` — current frontier tok/s, reference (llama.cpp), accuracy, VRAM.
- `passes` — the optimization journey (bars).
- `weights` / `labels` — emission weights and the eval verdict legend.
- `prs` — appended per evaluated PR: `{num, title, areas:[], label, tps, delta_pct, url}`.

The eval bot (`eval/pr_eval_bot.py`) can write `prs[]` and bump `status.frontier_tps` after each
run, so the page stays live with zero rebuild.

## Deploy (GitHub Pages)
It's plain static files. Enable Pages (Settings → Pages → deploy from `main`, root) and it serves at
`https://gittensor-ai-lab.github.io/sparkinfer/dashboard/`.
