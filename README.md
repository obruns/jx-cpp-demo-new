# A project to understand MR-based workflows

## Context

Coming from the commit-centric workflow of Gerrit and being in the
transition towards BitBucket for another project I got the impression
that BitBucket is not state-of-the-art and devs are slow to respond to
user wishes (e.g [BSERV-8384](https://jira.atlassian.com/browse/BSERV-8384)
which was even split into [BSERV-10559](https://jira.atlassian.com/browse/BSERV-10559)).

## Expectations

* full support of working at the commit-level rather than at the branch-level
  + require approval by at least N reviewers
  + being able to fetch any patchset for any changeset
    (`git fetch origin refs/changes/AB/XXXXAB/N`)
  + show differences between patchsets (i.e. the differences between force pushes
    to the to-be-merged branch)
  + [full control of the merge message](https://docs.gitlab.com/ce/user/project/merge_requests/squash_and_merge.html#overview)
  + `--squash --ff-only` merge strategy
  + [preserve Git authorship](https://docs.gitlab.com/ce/user/project/merge_requests/squash_and_merge.html#commit-metadata-for-squashed-commits)
* new features not offered by Gerrit
  + Web IDE
  + dependencies across feature branches of different projects (Zuul CI)
  + toggle auto-merge when CI pipeline passes
  + close merge request by pushing to master (see below)
    - this would require some magic in the server-side update hook to
      see if there are merge requests that resulted in the same tree if
      merged
    - [GitLab CE #55665](https://gitlab.com/gitlab-org/gitlab-ce/issues/55665)
  + [being able to close issues with 'Closes: #xxxx' and 'Fixes: #xxxx'](https://docs.gitlab.com/ce/user/project/issues/closing_issues.html#via-merge-request)
  + [cherry-pick from merge request](https://docs.gitlab.com/ce/user/project/merge_requests/cherry_pick_changes.html)
  + [support for rendering Jupyter notebook files as HTML](https://docs.gitlab.com/ce/user/project/repository/#jupyter-notebook-files)
  + [first multiline commit becomes the merge message](https://docs.gitlab.com/ce/user/project/merge_requests/squash_and_merge.html#overview)
  + [merge-request alias](https://docs.gitlab.com/ce/user/project/merge_requests/#checkout-locally-by-adding-a-git-alias)
    - BUT one can only access the latest state via the `merge-requests/N/head`
      reference
  + [Expire pipeline immediately when ${BRANCH} is updated](https://docs.microsoft.com/en-us/azure/devops/repos/git/branch-policies?view=azure-devops#build-validation)
  + [support for PlantUML in Markdown, AsciiDoc and reStructuredText](https://docs.gitlab.com/ce/administration/integration/plantuml.html#creating-diagrams)

```plantuml
Bob -> Alice : hello
Alice -> Bob : Go Away
```

## Nice-to-have

* [bypassing CI](https://docs.gitlab.com/ce/ci/yaml/README.html#onlychanges-and-exceptchanges) for merge requests that do not modify anything covered by
  CI, e.g. a commit that changes only this README
* bots, see [GitLab Bot](https://gitlab.com/gitlab-bot) and [kwrbot](https://gitlab.kitware.com/kwrobot)
  + clang-format, alternative: a hook
  + keep in mind that below messages are added by hand, when there should be full
    automation

```
Do: stage
Do: merge
Do: reformat
Do: test
Do: test --stop
```

## Merge strategies offered by GitLab

* Merge commit
* Merge commit with semi-linear history (`git merge --ff-only --no-ff`)
  + a rebase button is available in the UI if rebase is conflict-free
* Fast-forward merge (`git merge --ff-only`)
  + *can* be combined with a "squash all commits" toggle; in this case,
  summary and description of the MR are used as the message

## Merge strategies offered by BitBucket

* Merge Commit `--no-ff`
* Fast-Forward `--ff`
* Fast-Forward Only `--ff-only`
* Rebase and merge `rebase + merge --no-ff`
* Rebase and fast-forward `rebase + merge --ff-only`
* Squash `--squash`
  + this should be the only merge strategy allowed if one wants to mimic Gerrit
  + caveat: content of the merge message must be added on merge (Web UI)
  + caveat: BitBucket will always append the log of the merged branch
* Squash, fast-forward only `squash --ff-only`
  + usage is discouraged if the project is too active because of race conditions
    between merge requests

## Check out, review, and merge locally

Step 1. Fetch and check out the branch for this merge request

```
git fetch origin
git checkout -b feature/add-readme origin/feature/add-readme
```

Step 2. Review the changes locally

Step 3. Merge the branch and fix any conflicts that come up

```
git fetch origin
git checkout origin/master
git merge --no-ff feature/add-readme
```

Step 4. Push the result of the merge to GitLab

```
git push origin master
```

Tip: You can also checkout merge requests locally by [following these guidelines](https://gitlab.com/help/user/project/merge_requests/index.md#checkout-merge-requests-locally).

## Glossary

* changeset: In Gerrit a changeset is a commit published for review
* patchset: In Gerrit a patchset is an improvement of a changeset. Such
  improvements are created by amending a commit locally, making sure to add the
  appropriate Change-Id and pushing again to the magic reference
* [magic reference](https://gerrit-review.googlesource.com/Documentation/access-control.html#references_magic):
  Gerrit makes the server-side Git update hook listen for pushes to magic
  references and creates actual references of the form `changes/AB/XXXXAB/N`

[//]: # (vim:textwidth=80:shiftwidth=2:tabstob=2:softtabstop=2)
