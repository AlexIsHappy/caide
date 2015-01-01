module Caide.Commands.BuildScaffold (
      cmd
    , generateScaffoldSolution
) where

import Control.Applicative ((<$>))
import Control.Monad (forM_)
import Control.Monad.Except (catchError)
import Data.Maybe (mapMaybe)
import Filesystem.Path.CurrentOS (decodeString, (</>))

import Caide.Types
import Caide.Registry (findLanguage, findFeature)
import Caide.Configuration (getActiveProblem, readProblemState, getFeatures)


cmd :: CommandHandler
cmd = CommandHandler
    { command = "lang"
    , description = "Generate solution scaffold"
    , usage = "caide lang <language>"
    , action = generateScaffoldSolution
    }

generateScaffoldSolution :: [String] -> CaideIO ()
generateScaffoldSolution [lang] = case findLanguage lang of
    Nothing -> throw $ "Unknown or unsupported language: " ++ lang
    Just language -> do
        root <- caideRoot
        problem <- getActiveProblem `catchError` const (throw "No active problem. Generate one with `caide problem`")

        let problemDir = root </> decodeString problem
        generateScaffold language problemDir

        hProblem <- readProblemState problem
        setProp hProblem "problem" "language" lang

        features <- mapMaybe findFeature <$> getFeatures
        forM_ features $ \feature -> onProblemCodeCreated feature problem

generateScaffoldSolution _ = throw $ "Usage " ++ usage cmd

