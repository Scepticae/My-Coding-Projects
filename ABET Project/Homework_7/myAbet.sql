-- MySQL dump 10.14  Distrib 5.5.60-MariaDB, for Linux (x86_64)
--
-- Host: dbs.eecs.utk.edu    Database: cs465_sleonar5
-- ------------------------------------------------------
-- Server version	10.1.35-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `AssessmentTypes`
--

DROP TABLE IF EXISTS `AssessmentTypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `AssessmentTypes` (
  `assessmentId` int(11) NOT NULL,
  `type` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`assessmentId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `AssessmentTypes`
--

LOCK TABLES `AssessmentTypes` WRITE;
/*!40000 ALTER TABLE `AssessmentTypes` DISABLE KEYS */;
INSERT INTO `AssessmentTypes` VALUES (1,'Exam'),(2,'Quiz'),(3,'Homework'),(4,'Lab'),(5,'Programming Assignment'),(6,'Project'),(7,'Written Document'),(8,'Presentation'),(9,'Performance');
/*!40000 ALTER TABLE `AssessmentTypes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Assessments`
--

DROP TABLE IF EXISTS `Assessments`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Assessments` (
  `sectionId` int(11) NOT NULL,
  `assessmentId` int(11) NOT NULL,
  `outcomeId` char(2) NOT NULL,
  `outcomeMajor` enum('CS','CpE','EE') NOT NULL,
  `assessmentDescription` varchar(200) NOT NULL,
  `rubricId` varchar(10) NOT NULL,
  `weight` decimal(4,2) DEFAULT NULL,
  PRIMARY KEY (`sectionId`,`assessmentId`,`outcomeId`,`outcomeMajor`,`assessmentDescription`),
  KEY `outcomeId` (`outcomeId`,`outcomeMajor`),
  KEY `assessmentId` (`assessmentId`),
  KEY `rubricId` (`rubricId`),
  CONSTRAINT `Assessments_ibfk_1` FOREIGN KEY (`sectionId`) REFERENCES `SectionsHistory` (`sectionId`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `Assessments_ibfk_2` FOREIGN KEY (`outcomeId`, `outcomeMajor`) REFERENCES `Outcomes` (`outcomeId`, `outcomeMajor`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `Assessments_ibfk_3` FOREIGN KEY (`assessmentId`) REFERENCES `AssessmentTypes` (`assessmentId`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `Assessments_ibfk_4` FOREIGN KEY (`rubricId`) REFERENCES `Rubrics` (`rubricId`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Assessments`
--

LOCK TABLES `Assessments` WRITE;
/*!40000 ALTER TABLE `Assessments` DISABLE KEYS */;
INSERT INTO `Assessments` VALUES (988,1,'C1','CS','Exam on Super Computing','CS1-FA18',0.40),(989,8,'C1','CS','Final Software Engineering Presentation','CS2-FA18',0.30),(996,1,'C4','CS','Exam on professional responsibilities.','CS4-FA18',0.40),(996,6,'C2','CS','Design Component for Final Design Project.','CS2-FA18',0.75),(996,6,'C2','CS','Design Component for Preliminary Design Project.','CS2-FA18',0.25),(996,6,'C4','CS','Professional responsibilities component of final design project.','CS4-FA18',0.20),(996,6,'C4','CS','Professional responsibilities component of preliminary design project.','CS4-FA18',0.10),(996,6,'C5','CS','Team component of final design document.','CS5-FA18',0.20),(996,7,'C3','CS','Written Component for Final Design Document.','CS3-FA18',0.25),(996,7,'C3','CS','Written Component for Preliminary Design Document.','CS3-FA18',0.25),(996,7,'C4','CS','Written paper on an ethical issue in design.','CS4-FA18',0.30),(996,8,'C3','CS','Oral Presentation for Final Design Document.','CS3-FA18',0.25),(996,8,'C3','CS','Poster Presentation.','CS3-FA18',0.25),(996,8,'C5','CS','Team component of poster presentation.','CS5-FA18',0.20),(996,9,'C5','CS','Instructors’ assessment of student’s performance on the team throughout the semester.','CS5-FA18',0.40),(996,9,'C5','CS','Teammates’ assessment of student’s performance on the team.','CS5-FA18',0.20);
/*!40000 ALTER TABLE `Assessments` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `CourseMapping`
--

DROP TABLE IF EXISTS `CourseMapping`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CourseMapping` (
  `courseId` varchar(10) NOT NULL,
  `outcomeId` char(2) NOT NULL,
  `outcomeMajor` enum('CS','CpE','EE') NOT NULL,
  PRIMARY KEY (`courseId`,`outcomeId`,`outcomeMajor`),
  KEY `outcomeId` (`outcomeId`,`outcomeMajor`),
  CONSTRAINT `CourseMapping_ibfk_1` FOREIGN KEY (`courseId`) REFERENCES `Courses` (`courseId`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `CourseMapping_ibfk_2` FOREIGN KEY (`outcomeId`, `outcomeMajor`) REFERENCES `Outcomes` (`outcomeId`, `outcomeMajor`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CourseMapping`
--

LOCK TABLES `CourseMapping` WRITE;
/*!40000 ALTER TABLE `CourseMapping` DISABLE KEYS */;
INSERT INTO `CourseMapping` VALUES ('COSC312','C6','CS'),('COSC340','C2','CS'),('COSC340','C3','CS'),('COSC340','C5','CS'),('COSC340','C6','CS'),('COSC360','C1','CS'),('COSC365','C1','CS'),('COSC395','C4','CS'),('COSC402','C2','CS'),('COSC402','C3','CS'),('COSC402','C4','CS'),('COSC402','C5','CS'),('ECE255','E2','EE'),('ECE255','E6','CpE'),('ECE256','E1','CpE'),('ECE256','E6','CpE'),('ECE325','E2','EE'),('ECE325','E5','EE'),('ECE325','E6','EE'),('ECE335','E1','EE'),('ECE335','E2','EE'),('ECE335','E6','EE'),('ECE342','E1','EE'),('ECE342','E3','EE'),('ECE351','E1','CpE'),('ECE351','E2','CpE'),('ECE351','E5','CpE'),('ECE351','E6','CpE'),('ECE395','E1','CpE'),('ECE395','E4','CpE'),('ECE395','E4','EE'),('ECE395','E7','CpE'),('ECE395','E7','EE'),('ECE402','E2','CpE'),('ECE402','E2','EE'),('ECE402','E3','CpE'),('ECE402','E3','EE'),('ECE402','E4','CpE'),('ECE402','E4','EE'),('ECE402','E5','CpE'),('ECE402','E5','EE'),('ECE402','E7','CpE'),('ECE402','E7','EE');
/*!40000 ALTER TABLE `CourseMapping` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Courses`
--

DROP TABLE IF EXISTS `Courses`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Courses` (
  `courseId` varchar(10) NOT NULL,
  `courseTitle` varchar(45) NOT NULL,
  PRIMARY KEY (`courseId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Courses`
--

LOCK TABLES `Courses` WRITE;
/*!40000 ALTER TABLE `Courses` DISABLE KEYS */;
INSERT INTO `Courses` VALUES ('COSC312','Algorithm Analysis and Automata'),('COSC340','Software Engineering'),('COSC360','Systems Programming'),('COSC365','Programming Languages'),('COSC395','Junior Seminar'),('COSC402','Senior Design'),('ECE255','Intro to Logical Digital Design Sys'),('ECE256','Object-Oriented Programming'),('ECE315','Signals and Systems I'),('ECE325','Electric Energy System Components'),('ECE335','Electronic Devices'),('ECE342','Fundamentals of Communication'),('ECE351','Digital System Design'),('ECE395','Junior Seminar'),('ECE402','Senior Design');
/*!40000 ALTER TABLE `Courses` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Instructors`
--

DROP TABLE IF EXISTS `Instructors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Instructors` (
  `instructorId` varchar(15) NOT NULL,
  `instructorFirstName` varchar(45) NOT NULL,
  `instructorLastName` varchar(45) DEFAULT NULL,
  `instructorEmail` varchar(45) NOT NULL,
  `instructorPassword` varchar(20) NOT NULL,
  PRIMARY KEY (`instructorId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Instructors`
--

LOCK TABLES `Instructors` WRITE;
/*!40000 ALTER TABLE `Instructors` DISABLE KEYS */;
INSERT INTO `Instructors` VALUES ('bvz2018','Brad','Vanderzanden','bvz2018@utk.edu','bestTeacher'),('cQiong18','Charles','Qiong','cQiong18@utk.edu','compOps'),('jHuang18','Jian','Huang','jHuang18@utk.edu','coolHacker'),('jPlank18','Jim','Plank','jPlank18@utk.edu','bestCoder'),('mBerry18','Michael','Berry','mBerry18@utk.edu','smartGuy'),('mJantz18','Michael','Jantz','mJantz18@utk.edu','compileGuy'),('mVose2018','Michael','Vose','mVose2018@utk.edu','mrSporadic'),('sMarz2018','Stephen','Marz','sMarz2018@utk.edu','newKid');
/*!40000 ALTER TABLE `Instructors` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Narratives`
--

DROP TABLE IF EXISTS `Narratives`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Narratives` (
  `sectionId` int(11) NOT NULL,
  `outcomeId` char(2) NOT NULL,
  `outcomeMajor` enum('CS','CpE','EE') NOT NULL,
  `strengths` varchar(500) DEFAULT NULL,
  `weaknesses` varchar(500) DEFAULT NULL,
  `actions` varchar(500) DEFAULT NULL,
  PRIMARY KEY (`sectionId`,`outcomeId`,`outcomeMajor`),
  KEY `outcomeId` (`outcomeId`,`outcomeMajor`),
  CONSTRAINT `Narratives_ibfk_1` FOREIGN KEY (`sectionId`) REFERENCES `SectionsHistory` (`sectionId`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `Narratives_ibfk_2` FOREIGN KEY (`outcomeId`, `outcomeMajor`) REFERENCES `Outcomes` (`outcomeId`, `outcomeMajor`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Narratives`
--

LOCK TABLES `Narratives` WRITE;
/*!40000 ALTER TABLE `Narratives` DISABLE KEYS */;
INSERT INTO `Narratives` VALUES (996,'C2','CS','Good use of software engineering techniques to organize project. Good use of concepts from core \nCS courses in designing the solution.','Students needed to be coached to come up with multiple alternative designs. They were often too focused \non a single design solution. Student evaluation of their designs seemed rushed and a bit superficial.','Add a lecture on how to think outside the box to \nwiden students’ perspective when coming up with alternative designs. Add a block of instructions to the preliminary design document assignment that \nexplains the need for alternative designs. Change the deadlines for the various project phases so that students have more time to evaluate their projects \nat the end of the semester.'),(996,'C3','CS','Speaking in front of group. Students were confident about their material.','Students need to make\nbetter eye contact with the audience. Students need to project their voice more so people in the back of room can hear.','Add 1 or 2 more speaking \nengagements. Specify the importance of practicing speaking material in order to feel more comfortable.'),(996,'C4','CS','Students made good judgment in their computing exercises.','Students need to make sure their\ncomputation results are displayed more professionally.','Focus more on how to display results in a readable and interpretable manner.'),(996,'C5','CS','Students worked effectively as a team in order to complete the project in a timely manner.','Student\nworkloads were not evenly distributed.','Stress the importance of recognizing each members strengths and weaknesses to better distribute the workload\nevenly.');
/*!40000 ALTER TABLE `Narratives` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `OutcomeResults`
--

DROP TABLE IF EXISTS `OutcomeResults`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `OutcomeResults` (
  `sectionId` int(11) NOT NULL,
  `outcomeId` char(2) NOT NULL,
  `outcomeMajor` enum('CS','CpE','EE') NOT NULL,
  `performanceLevel` enum('NME','ME','EE') NOT NULL,
  `numberOfStudents` int(11) DEFAULT NULL,
  PRIMARY KEY (`sectionId`,`outcomeId`,`outcomeMajor`,`performanceLevel`),
  KEY `outcomeId` (`outcomeId`,`outcomeMajor`),
  KEY `performanceLevel` (`performanceLevel`),
  CONSTRAINT `OutcomeResults_ibfk_1` FOREIGN KEY (`sectionId`) REFERENCES `SectionsHistory` (`sectionId`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `OutcomeResults_ibfk_2` FOREIGN KEY (`outcomeId`, `outcomeMajor`) REFERENCES `Outcomes` (`outcomeId`, `outcomeMajor`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `OutcomeResults_ibfk_3` FOREIGN KEY (`performanceLevel`) REFERENCES `PerformanceLevels` (`performanceLevel`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `OutcomeResults`
--

LOCK TABLES `OutcomeResults` WRITE;
/*!40000 ALTER TABLE `OutcomeResults` DISABLE KEYS */;
INSERT INTO `OutcomeResults` VALUES (984,'E1','CpE','NME',5),(984,'E1','CpE','ME',11),(984,'E1','CpE','EE',9),(984,'E2','CpE','NME',7),(984,'E2','CpE','ME',10),(984,'E2','CpE','EE',8),(984,'E5','CpE','NME',5),(984,'E5','CpE','ME',12),(984,'E5','CpE','EE',8),(984,'E6','CpE','NME',4),(984,'E6','CpE','ME',15),(984,'E6','CpE','EE',6),(985,'E1','EE','NME',5),(985,'E1','EE','ME',15),(985,'E1','EE','EE',10),(985,'E2','EE','NME',6),(985,'E2','EE','ME',16),(985,'E2','EE','EE',8),(985,'E6','EE','NME',4),(985,'E6','EE','ME',15),(985,'E6','EE','EE',11),(987,'E2','EE','NME',4),(987,'E2','EE','ME',17),(987,'E2','EE','EE',13),(987,'E6','CpE','NME',3),(987,'E6','CpE','ME',18),(987,'E6','CpE','EE',16),(988,'C1','CS','NME',6),(988,'C1','CS','ME',21),(988,'C1','CS','EE',11),(989,'C1','CS','NME',3),(989,'C1','CS','ME',7),(989,'C1','CS','EE',5),(989,'C2','CS','NME',4),(989,'C2','CS','ME',18),(989,'C2','CS','EE',15),(989,'C3','CS','NME',6),(989,'C3','CS','ME',18),(989,'C3','CS','EE',13),(989,'C5','CS','NME',5),(989,'C5','CS','ME',19),(989,'C5','CS','EE',13),(989,'C6','CS','NME',7),(989,'C6','CS','ME',20),(989,'C6','CS','EE',11),(990,'C6','CS','NME',8),(990,'C6','CS','ME',18),(990,'C6','CS','EE',23),(991,'E2','CpE','NME',5),(991,'E2','CpE','ME',30),(991,'E2','CpE','EE',20),(991,'E2','EE','NME',4),(991,'E2','EE','ME',18),(991,'E2','EE','EE',18),(991,'E3','CpE','NME',7),(991,'E3','CpE','ME',30),(991,'E3','CpE','EE',18),(991,'E3','EE','NME',6),(991,'E3','EE','ME',18),(991,'E3','EE','EE',16),(991,'E4','CpE','NME',3),(991,'E4','CpE','ME',30),(991,'E4','CpE','EE',22),(991,'E4','EE','NME',1),(991,'E4','EE','ME',19),(991,'E4','EE','EE',20),(991,'E5','CpE','NME',1),(991,'E5','CpE','ME',34),(991,'E5','CpE','EE',20),(991,'E5','EE','NME',5),(991,'E5','EE','ME',17),(991,'E5','EE','EE',18),(991,'E7','CpE','NME',2),(991,'E7','CpE','ME',20),(991,'E7','CpE','EE',23),(991,'E7','EE','NME',6),(991,'E7','EE','ME',17),(991,'E7','EE','EE',17),(992,'E1','CpE','NME',6),(992,'E1','CpE','ME',12),(992,'E1','CpE','EE',12),(992,'E4','CpE','NME',6),(992,'E4','CpE','ME',14),(992,'E4','CpE','EE',10),(992,'E4','EE','NME',9),(992,'E4','EE','ME',15),(992,'E4','EE','EE',13),(992,'E7','CpE','NME',5),(992,'E7','CpE','ME',14),(992,'E7','CpE','EE',11),(992,'E7','EE','NME',9),(992,'E7','EE','ME',14),(992,'E7','EE','EE',14),(993,'E1','EE','NME',4),(993,'E1','EE','ME',12),(993,'E1','EE','EE',10),(993,'E3','EE','NME',5),(993,'E3','EE','ME',13),(993,'E3','EE','EE',8),(994,'E2','EE','NME',2),(994,'E2','EE','ME',13),(994,'E2','EE','EE',20),(994,'E5','EE','NME',2),(994,'E5','EE','ME',15),(994,'E5','EE','EE',18),(994,'E6','EE','NME',4),(994,'E6','EE','ME',14),(994,'E6','EE','EE',17),(995,'E1','CpE','NME',7),(995,'E1','CpE','ME',18),(995,'E1','CpE','EE',12),(995,'E6','CpE','NME',8),(995,'E6','CpE','ME',14),(995,'E6','CpE','EE',15),(996,'C2','CS','NME',9),(996,'C2','CS','ME',32),(996,'C2','CS','EE',38),(996,'C3','CS','NME',7),(996,'C3','CS','ME',30),(996,'C3','CS','EE',42),(996,'C4','CS','NME',9),(996,'C4','CS','ME',40),(996,'C4','CS','EE',30),(996,'C5','CS','NME',12),(996,'C5','CS','ME',32),(996,'C5','CS','EE',35),(997,'C4','CS','NME',13),(997,'C4','CS','ME',32),(997,'C4','CS','EE',26),(998,'C1','CS','NME',10),(998,'C1','CS','ME',20),(998,'C1','CS','EE',18),(999,'C1','CS','NME',7),(999,'C1','CS','ME',19),(999,'C1','CS','EE',22);
/*!40000 ALTER TABLE `OutcomeResults` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Outcomes`
--

DROP TABLE IF EXISTS `Outcomes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Outcomes` (
  `outcomeId` char(2) NOT NULL,
  `outcomeMajor` enum('CS','CpE','EE') NOT NULL,
  `outcomeDescription` varchar(300) DEFAULT NULL,
  `outcomeRubric` varchar(10) NOT NULL,
  PRIMARY KEY (`outcomeId`,`outcomeMajor`),
  KEY `outcomeRubric` (`outcomeRubric`),
  CONSTRAINT `Outcomes_ibfk_1` FOREIGN KEY (`outcomeRubric`) REFERENCES `Rubrics` (`rubricId`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Outcomes`
--

LOCK TABLES `Outcomes` WRITE;
/*!40000 ALTER TABLE `Outcomes` DISABLE KEYS */;
INSERT INTO `Outcomes` VALUES ('C1','CS','Analyze a computing problem and apply principles of computing to identify solutions.','CS1-FA18'),('C2','CS','Design a computing-based solution to meet requirements.','CS2-FA18'),('C3','CS','Communicate effectively.','CS3-FA18'),('C4','CS','Recognize professional responsibilities.','CS4-FA18'),('C5','CS','Function effectively on teams.','CS5-FA18'),('C6','CS','Apply theory and software development fundamentals to produce computing-based solutions.','CS6-FA18'),('E1','CpE','Identify, formulate, and solve complex engineering problems.','EC1-FA18'),('E1','EE','Identify, formulate, and solve complex engineering problems.','EC1-FA18'),('E2','CpE','Apply engineering design to produce solutions that meet specified needs.','EC2-FA18'),('E2','EE','Apply engineering design to produce solutions that meet specified needs.','EC2-FA18'),('E3','CpE','Communicate effectively with a range of audiences.','EC3-FA18'),('E3','EE','Communicate effectively with a range of audiences.','EC3-FA18'),('E4','CpE','Recognize ethical and professional responsibilities in engineering situations.','EC4-FA18'),('E4','EE','Recognize ethical and professional responsibilities in engineering situations.','EC4-FA18'),('E5','CpE','Function effectively on a team.','EC5-FA18'),('E5','EE','Function effectively on a team.','EC5-FA18'),('E6','CpE','Develop and conduct appropriate experimentation, analyze and interpret data.','EC6-FA18'),('E6','EE','Develop and conduct appropriate experimentation, analyze and interpret data.','EC6-FA18'),('E7','CpE','Apply new knowledge as needed, using appropriate learning strategies.','EC7-FA18'),('E7','EE','Apply new knowledge as needed, using appropriate learning strategies.','EC7-FA18');
/*!40000 ALTER TABLE `Outcomes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PerformanceLevels`
--

DROP TABLE IF EXISTS `PerformanceLevels`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PerformanceLevels` (
  `performanceLevel` enum('NME','ME','EE') NOT NULL,
  `description` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`performanceLevel`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PerformanceLevels`
--

LOCK TABLES `PerformanceLevels` WRITE;
/*!40000 ALTER TABLE `PerformanceLevels` DISABLE KEYS */;
INSERT INTO `PerformanceLevels` VALUES ('NME','Not Meets Expectations'),('ME','Meets Expectations'),('EE','Exceeds Expectations');
/*!40000 ALTER TABLE `PerformanceLevels` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Rubrics`
--

DROP TABLE IF EXISTS `Rubrics`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Rubrics` (
  `rubricId` varchar(10) NOT NULL,
  `performanceLevel` enum('NME','ME','EE') NOT NULL,
  `description` varchar(1000) DEFAULT NULL,
  PRIMARY KEY (`rubricId`,`performanceLevel`),
  KEY `performanceLevel` (`performanceLevel`),
  CONSTRAINT `Rubrics_ibfk_1` FOREIGN KEY (`performanceLevel`) REFERENCES `PerformanceLevels` (`performanceLevel`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Rubrics`
--

LOCK TABLES `Rubrics` WRITE;
/*!40000 ALTER TABLE `Rubrics` DISABLE KEYS */;
INSERT INTO `Rubrics` VALUES ('CS1-FA18','NME','Serious problems exist, including any or all of the following: 1) Examined, formulated, and analyzed few customer \nrequirements, 2) provided insufficient insight on how these components satisfy the requirements and the design of the target process or system.'),('CS1-FA18','ME','Examines, formulates and analyzes aspects of a process or system design that meets most customer requirements \nand identifies the computing components needed to meet these requirements.  Provides sufficient insight on how these components satisfy the requirements and the \ndesign of the target process or system.'),('CS1-FA18','EE','Examines, formulates and analyzes aspects of a process or system design that meets all customer requirements \nand identifies the computing components needed to meet these requirements.  Provides comprehensive insight on how these components satisfy the requirements and \nthe design of the target process or system.'),('CS2-FA18','NME','Serious problems exist, including any or all of the following: 1) Examined, formulated, and analyzed few \nnon-technical constraints, 2) provided insufficient insight on how these constraints impact the requirements and the design of the target process or system.'),('CS2-FA18','ME','Examines, formulates and analyzes aspects of a process or system design that meets most customer requirements \nin the context of non-technical constraints (economic, environment, social, safety, etc.).  Provides sufficient insight on how these constraints impact the requirements \nand the design of the target process or system.'),('CS2-FA18','EE','Examines, formulates and analyzes aspects of a process or system design that meets all customer requirements \nin the context of non-technical constraints (economic, environment, social, safety, etc.).  Provides comprehensive insight on how these constraints impact the \nrequirements and the design of the target process or system.'),('CS3-FA18','NME','Submits poorly written, poorly organized, poorly reasoned, and/or poorly supported (inadequate citations) \ndocuments. Communicates ineffectively during oral presentations because many elements of the presentation are executed poorly, such as improper pacing, confused \norganization, lack of clarity while speaking, excessive reading from notes, or not facing the audience. Prepares visual aids that either do not aid or detract from the \nwritten or oral presentation, because they are too busy, visually unappealing, or present information ineffectively.'),('CS3-FA18','ME','Submits written documents that communicate the relevant material but may have some grammatical errors, may \nhave some sections that seem out of place, may not make points as clearly as might be possible, or may lack some appropriate citations. Communicates adequately \nduring oral presentations but some aspects of the presentation, such as pacing, organization, clarity of speaking, reading from notes, or facing the audience rather \nthan slides can be improved. Prepares visual aids that usually complement and support the written or oral presentation, but some may lack effectiveness because they \nare too busy, visually unappealing, or do not present information in the most effective manner.'),('CS3-FA18','EE','Submits well-written, well-organized, and well-reasoned documents that are well-supported if necessary by \nappropriate citations, speaks clearly and articulately during presentations, and prepares visual aids that complement, support, and significantly enhance either the \nwritten or oral presentation.'),('CS4-FA18','NME','Identifies few if any of the key aspects of the issue, provides either a superficial discussion of the relevant \nalternative views of these key aspects or fails to identify and discuss multiple alternative views, and provides a non-compelling argument for how to resolve the issue.'),('CS4-FA18','ME','Identifies most of the key aspects of the issue, satisfactorily discusses most of the relevant alternative views of these \nkey aspects, and provides an adequate argument for how to resolve the issue.'),('CS4-FA18','EE','Comprehensively identifies the key aspects of the issue, insightfully discusses alternative views of these key aspects, \nand provides a convincing argument for how to resolve the issue.'),('CS5-FA18','NME','Fails to complete assigned tasks on time, incompletely finishes tasks, thus forcing teammates to cover for the \nstudent, and/or demonstrates insufficient regard for teammates’ viewpoints.'),('CS5-FA18','ME','Performs assigned tasks but may require some prompting, completes assigned tasks in a satisfactory manner, and \nmakes an acceptable effort to gather, respect, and integrate teammates’ viewpoints.'),('CS5-FA18','EE','Performs assigned tasks on-time and without prompting, completes assigned tasks in an exemplary manner, and \nactively gathers, respects, and integrates teammates’ viewpoints.'),('CS6-FA18','NME','Serious problems exist, including any or all of the following: 1) Demonstrates poor comprehension of the \ncomputing and mathematical concepts required to solve the problem, 2) Uses few of the relevant computing and mathematical algorithms and processes required to \nsolve the problem and 3) if asked, provides insufficient insight on the advantages and disadvantages of the solution chosen using well established computing and \nmathematical methodologies.'),('CS6-FA18','ME','Demonstrates sufficient comprehension of the computing and mathematical concepts required to solve a problem \nand correctly applies most of the relevant concepts to its solution. If asked to do so, the student provides sufficient insight on the advantages and disadvantages of the \nsolution chosen using well established computing and mathematical methodologies.'),('CS6-FA18','EE','Demonstrates excellent comprehension of the computing and mathematical concepts required to solve a problem \nand applies these concepts almost flawlessly to its solution. If asked to do so, the student provides comprehensive insight on the advantages and disadvantages of the \nsolution chosen using well established computing and mathematical methodologies.'),('EC1-FA18','NME','Serious problems exist in the student’s ability to identify, formulate, and solve the problem, including any or all \nof the following: 1) Identifies, formulates and analyzes few of the requirements for the problem, 2) uses few of the engineering components needed to meet these \nrequirements, 3) provided insufficient insight on how these components satisfy the requirements of the target problem, 4) organizes the required components into a \npoor design, and 5) implements the required components incorrectly or in a hazardous manner.'),('EC1-FA18','ME','Identifies, formulates and analyzes most requirements for the problem and identifies most of the engineering \ncomponents needed to meet these requirements. Provides sufficient insight on how these components satisfy the requirements of the target problem, organizes these \ncomponents into a sufficient design, and implements these components satisfactorily but maybe not in the most elegant manner.'),('EC1-FA18','EE','Identifies, formulates and analyzes all requirements for the problem and identifies the engineering components \nneeded to meet these requirements.  Provides comprehensive insight on how these components satisfy the requirements of the target problem, organizes these \ncomponents into a comprehensive design, and implements these components almost flawlessly.'),('EC2-FA18','NME','Serious problems exist, including any or all of the following: 1) Examined, formulated, and analyzed few \nconstraints, 2) provided insufficient insight on how these constraints impact the requirements and the design of the target process or system.'),('EC2-FA18','ME','Examines, formulates and analyzes aspects of a process or system design that meets most customer requirements \nin the context of both technical and non-technical constraints (economic, environment, social, safety, etc.). Provides sufficient insight on how these constraints impact \nthe requirements and the design of the target process or system.'),('EC2-FA18','EE','Examines, formulates and analyzes aspects of a process or system design that meets all customer requirements in \nthe context of both technical and non-technical constraints (economic, environment, social, safety, etc.).  Provides comprehensive insight on how these constraints \nimpact the requirements and the design of the target process or system.'),('EC3-FA18','NME','Submits poorly written, poorly organized, poorly reasoned, and/or poorly supported (inadequate citations) \ndocuments. Communicates ineffectively during oral presentations because many elements of the presentation are executed poorly, such as improper pacing, confused \norganization, lack of clarity while speaking, excessive reading from notes, or not facing the audience. Prepares visual aids that either do not aid or detract from the \nwritten or oral presentation, because they are too busy, visually unappealing, or present information ineffectively.'),('EC3-FA18','ME','Submits written documents that communicate the relevant material but may have some grammatical errors, may \nhave some sections that seem out of place, may not make points as clearly as might be possible, or may lack some appropriate citations. Communicates adequately \nduring oral presentations but some aspects of the presentation, such as pacing, organization, clarity of speaking, reading from notes, or facing the audience rather than \nslides can be improved. Prepares visual aids that usually complement and support the written or oral presentation, but some may lack effectiveness because they are \ntoo busy, visually unappealing, or do not present information in the most effective manner.'),('EC3-FA18','EE','Submits well-written, well-organized, and well-reasoned documents that are well-supported if necessary by \nappropriate citations, speaks clearly and articulately during presentations, and prepares visual aids that complement, support, and significantly enhance either the \nwritten or oral presentation.'),('EC4-FA18','NME','Identifies few if any of the key professional and ethical aspects of the issue, provides either a superficial \ndiscussion of the relevant alternative views of these key aspects or fails to identify and discuss multiple alternative views, and provides a non-compelling argument for \nhow to professionally and ethically resolve the issue.'),('EC4-FA18','ME','Identifies most of the key professional and ethical aspects of the issue, satisfactorily discusses most of the relevant \nalternative views of these key aspects, and provides an adequate argument for how to professional and ethically resolve the issue.'),('EC4-FA18','EE','Comprehensively identifies the key professional and ethical aspects of the issue, insightfully discusses alternative \nviews of these key aspects, and provides a convincing argument for how to professionally and ethically resolve the issue'),('EC5-FA18','NME','Fails to complete assigned tasks on time, incompletely finishes tasks, thus forcing teammates to cover for the \nstudent, and/or demonstrates insufficient regard for teammates’ viewpoints'),('EC5-FA18','ME','Performs assigned tasks but may require some prompting, completes assigned tasks in a satisfactory manner, and \nmakes an acceptable effort to gather, respect, and integrate teammates’ viewpoints.'),('EC5-FA18','EE','Performs assigned tasks on-time and without prompting, completes assigned tasks in an exemplary manner, and \nactively gathers, respects, and integrates teammates’ viewpoints.'),('EC6-FA18','NME','Serious problems exist in the student’s experimental technique including any or all of the following 1) prepares a \nflawed design for the experiment, 2) fails to follow the experimental plan, 3) acquires data on few of the appropriate experimental variables, 4) provides few \ncomparisons between experimental data and results to appropriate theoretical models, and 5) correctly explains few of the differences between the experimental data \nand the theoretical models.'),('EC6-FA18','ME','Displays sufficient insight into the experimental technique and how to perform it: 1) adequately designs an \nexperiment, 2) mostly follows an experimental plan, 3) acquires data on most of the appropriate experimental variables, 4) compares experimental data and results to \nmost of the appropriate theoretical models, and 5) correctly explains most of the differences between the experimental data and the theoretical models.'),('EC6-FA18','EE','Displays comprehensive insight on how to 1) design an experiment, 2) follow an experimental plan, 3) acquire data \non appropriate experimental variables, 4) compare experimental data and results to appropriate theoretical models, and 5) explain any differences between the \nexperimental data and the theoretical models.'),('EC7-FA18','NME','Flounders in novel situations. The student finds it difficult to explore appropriate informational resources, \nidentifies few of the relevant resources, and/or experiences difficulty integrating new information from these sources with existing knowledge, and as a result fails to \nprovide a satisfactory conclusion to this novel situation. The student generally requires considerable coaching in order to identify appropriate informational resources or \nto integrate new knowledge with existing knowledge.'),('EC7-FA18','ME','Demonstrates an adequate capability in novel situations to explore appropriate informational resources, identify \nmost of the relevant resources, and integrate new information from these sources with existing knowledge to provide a satisfactory conclusion to this novel situation. \nThe student may require some coaching in identifying appropriate informational resources or in integrating new knowledge with existing knowledge.'),('EC7-FA18','EE','Demonstrates a superlative capability in novel situations to independently explore appropriate informational \nresources, identify the relevant resources, and integrate new information from these sources with existing knowledge to provide an insightful conclusion to this \nnovel situation.');
/*!40000 ALTER TABLE `Rubrics` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SectionsCurrent`
--

DROP TABLE IF EXISTS `SectionsCurrent`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `SectionsCurrent` (
  `sectionId` int(11) NOT NULL AUTO_INCREMENT,
  `instructorId` varchar(15) NOT NULL,
  `sectionSemester` varchar(5) NOT NULL,
  `courseId` varchar(10) NOT NULL,
  `sectionYear` year(4) NOT NULL,
  PRIMARY KEY (`sectionId`),
  KEY `courseId` (`courseId`),
  KEY `instructorId` (`instructorId`),
  CONSTRAINT `SectionsCurrent_ibfk_1` FOREIGN KEY (`courseId`) REFERENCES `Courses` (`courseId`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `SectionsCurrent_ibfk_2` FOREIGN KEY (`instructorId`) REFERENCES `Instructors` (`instructorId`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=1007 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `SectionsCurrent`
--

LOCK TABLES `SectionsCurrent` WRITE;
/*!40000 ALTER TABLE `SectionsCurrent` DISABLE KEYS */;
INSERT INTO `SectionsCurrent` VALUES (1000,'mBerry18','Fall','COSC312',2018),(1001,'sMarz2018','Fall','COSC340',2018),(1002,'jPlank18','Fall','COSC360',2018),(1003,'mVose2018','Fall','ECE255',2018),(1004,'mBerry18','Fall','ECE315',2018),(1005,'mJantz18','Fall','ECE335',2018),(1006,'mVose2018','Fall','ECE351',2018);
/*!40000 ALTER TABLE `SectionsCurrent` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SectionsHistory`
--

DROP TABLE IF EXISTS `SectionsHistory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `SectionsHistory` (
  `sectionId` int(11) NOT NULL AUTO_INCREMENT,
  `instructorId` varchar(15) NOT NULL,
  `sectionSemester` varchar(7) NOT NULL,
  `courseId` varchar(10) NOT NULL,
  `sectionYear` year(4) NOT NULL,
  PRIMARY KEY (`sectionId`),
  KEY `courseId` (`courseId`),
  KEY `instructorId` (`instructorId`),
  CONSTRAINT `SectionsHistory_ibfk_1` FOREIGN KEY (`courseId`) REFERENCES `Courses` (`courseId`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `SectionsHistory_ibfk_2` FOREIGN KEY (`instructorId`) REFERENCES `Instructors` (`instructorId`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=1000 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `SectionsHistory`
--

LOCK TABLES `SectionsHistory` WRITE;
/*!40000 ALTER TABLE `SectionsHistory` DISABLE KEYS */;
INSERT INTO `SectionsHistory` VALUES (984,'mVose2018','Fall','ECE351',2017),(985,'mJantz18','Fall','ECE335',2017),(986,'mBerry18','Fall','ECE315',2017),(987,'mVose2018','Fall','ECE255',2017),(988,'jPlank18','Fall','COSC360',2017),(989,'sMarz2018','Fall','COSC340',2017),(990,'mBerry18','Fall','COSC312',2017),(991,'jPlank18','Spring','ECE402',2018),(992,'mVose2018','Spring','ECE395',2018),(993,'mJantz18','Spring','ECE342',2018),(994,'mBerry18','Spring','ECE325',2018),(995,'mVose2018','Spring','ECE256',2018),(996,'jPlank18','Spring','COSC402',2018),(997,'sMarz2018','Spring','COSC395',2018),(998,'jHuang18','Spring','COSC360',2018),(999,'bvz2018','Spring','COSC365',2018);
/*!40000 ALTER TABLE `SectionsHistory` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-11-18  4:19:47
