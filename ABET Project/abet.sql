SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Table `Instructors`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Instructors` (
  `instructorId` INT NOT NULL AUTO_INCREMENT,
  `instructorFirstName` VARCHAR(45) NOT NULL,
  `instructorLastName` VARCHAR(45) NULL,
  `instructorEmail` VARCHAR(45) NOT NULL,
  `instructorPassword` VARCHAR(20) NOT NULL,
  PRIMARY KEY (`instructorId`));



-- -----------------------------------------------------
-- Table `Courses`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Courses` (
  `courseId` INT NOT NULL AUTO_INCREMENT,
  `courseName` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`courseId`));


-- -----------------------------------------------------
-- Table `SectionsCurrent`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `SectionsCurrent` (
  `sectionId` INT NOT NULL AUTO_INCREMENT,
  `instructorId` INT NOT NULL,
  `sectionSemester` VARCHAR(5) NOT NULL,
  `courseId` INT NOT NULL,
  `sectionYear` YEAR NOT NULL,
  PRIMARY KEY (`sectionId`),
  INDEX `fk_Sections_Courses1_idx` (`courseId` ASC),
  INDEX `fk_Sections_Instructors1_idx` (`instructorId` ASC),
  CONSTRAINT `fk_Sections_Courses1`
    FOREIGN KEY (`courseId`)
    REFERENCES `Courses` (`courseId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_UsersToSections_Users1`
    FOREIGN KEY (`instructorId`)
    REFERENCES `Instructors` (`instructorId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);
-- -----------------------------------------------------
-- Table `Outcomes`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `Outcomes` (
  `outcomeId` CHAR(2) NOT NULL,
  `outcomeMajor` enum("CS", "CpE", "EE") NOT NULL,
  `outcomeDescription` VARCHAR(100) NULL,
  `outcomeRubric` INT NOT NULL,
  PRIMARY KEY (`outcomeId`, `outcomeMajor`),
  INDEX `fk_Outcomes_Rubrics1_idx` (`outcomeRubric` ASC),
  CONSTRAINT `fk_Outcomes_Rubrics1`
    FOREIGN KEY (`outcomeRubric`)
    REFERENCES `Rubrics` (`rubricId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);

-- -----------------------------------------------------
-- Table `CourseMapping`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `CourseMapping` (
  `courseId` INT NOT NULL,
  `outcomeId` CHAR(2) NOT NULL,
  `outcomeMajor` enum("CS", "CpE", "EE") NOT NULL,
  PRIMARY KEY (`courseId`, `outcomeId`, `outcomeMajor`),
  INDEX `fk_Courses_has_Outcomes_Outcomes1_idx` (`outcomeId` ASC, `outcomeMajor` ASC),
  INDEX `fk_Courses_has_Outcomes_Courses1_idx` (`courseId` ASC),
  CONSTRAINT `fk_Courses_has_Outcomes_Courses1`
    FOREIGN KEY (`courseId`)
    REFERENCES `Courses` (`courseId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Courses_has_Outcomes_Outcomes1`
    FOREIGN KEY (`outcomeId` , `outcomeMajor`)
    REFERENCES `Outcomes` (`outcomeId` , `outcomeMajor`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
