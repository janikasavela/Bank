CREATE DATABASE  IF NOT EXISTS `pankki` /*!40100 DEFAULT CHARACTER SET utf8mb3 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `pankki`;
-- MySQL dump 10.13  Distrib 8.0.30, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: pankki
-- ------------------------------------------------------
-- Server version	8.0.29

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `asiakas`
--

DROP TABLE IF EXISTS `asiakas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakas` (
  `id_asiakas` int NOT NULL AUTO_INCREMENT,
  `etunimi` varchar(50) NOT NULL,
  `sukunimi` varchar(50) NOT NULL,
  `osoite` varchar(55) NOT NULL,
  `puhnum` char(15) DEFAULT NULL,
  PRIMARY KEY (`id_asiakas`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakas`
--

LOCK TABLES `asiakas` WRITE;
/*!40000 ALTER TABLE `asiakas` DISABLE KEYS */;
INSERT INTO `asiakas` VALUES (1,'Jaana','Korhonen','Kalevankatu 1','0400601234'),(2,'Aada','Korhonen','Kalevankatu 1','0400601111'),(3,'Aapo','Korhonen','Kalevankatu 1','0400602222'),(4,'Lari','Virtanen','Mikonkatu 2','0400601233'),(5,'Maaret','Mäkinen','Sofiankatu 4','0407698888'),(6,'Anette','Heikkinen','Tehtaankatu 3','0401234567'),(7,'Jarmo','Heikkinen','Tehtaankatu 3','0401234333');
/*!40000 ALTER TABLE `asiakas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `kortti`
--

DROP TABLE IF EXISTS `kortti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kortti` (
  `id_kortti` char(4) NOT NULL,
  `pin_koodi` varchar(255) NOT NULL,
  `id_asiakas` int NOT NULL,
  `credit` tinyint DEFAULT '0',
  PRIMARY KEY (`id_kortti`),
  KEY `asiakas_kortti_idx` (`id_asiakas`),
  CONSTRAINT `asiakas_kortti` FOREIGN KEY (`id_asiakas`) REFERENCES `asiakas` (`id_asiakas`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kortti`
--

LOCK TABLES `kortti` WRITE;
/*!40000 ALTER TABLE `kortti` DISABLE KEYS */;
INSERT INTO `kortti` VALUES ('1010','$2a$10$o47Eq.vWYImDB7yW/bsvd.7S6HJCcn/e5wlYoM7fJeNYjGZltWrD2',2,0),('1011','$2a$10$7eKipJIB8K4.fQ17oexxNeuhHEalJGaMPi3..AdwLdECMI/Pqr/KW',3,0),('1012','$2a$10$V6ywxeAq4igij/AdfG4He.nWxggqRNSDvmNkOOe57.YpfwM3YNZam',1,1),('1013','$2a$10$oE3vQVmr51e4CU5IotnM1ed5mJyvd8mr7M29NjryfdA7Nf8chJ7ma',6,1),('1014','$2a$10$1rm4O/6sCAK6C7z5mDK0N.O5mnxDblDKQIE7B1.A2UlSpf2yNVHaC',7,1),('1015','$2a$10$USbfH0Ydxo5NlMzf2p.mYuIkmeXvEzY644gQ8am8Nwvb4amYfLksS',4,0),('1016','$2a$10$aeO6tjNscuJUJNTQrYglauztRagufNoFZIjvvjxuWkmOzGtAORk2a',5,1);
/*!40000 ALTER TABLE `kortti` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `oikeudet`
--

DROP TABLE IF EXISTS `oikeudet`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `oikeudet` (
  `id_oikeudet` int NOT NULL AUTO_INCREMENT,
  `id_kortti` char(4) NOT NULL,
  `id_tilinumero` int NOT NULL,
  PRIMARY KEY (`id_oikeudet`),
  KEY `tilinumero_oikeudet_idx` (`id_tilinumero`),
  KEY `kortti_oikeudet_idx` (`id_kortti`),
  CONSTRAINT `kortti_oikeudet` FOREIGN KEY (`id_kortti`) REFERENCES `kortti` (`id_kortti`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `tilinumero_oikeudet` FOREIGN KEY (`id_tilinumero`) REFERENCES `tili` (`id_tilinumero`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `oikeudet`
--

LOCK TABLES `oikeudet` WRITE;
/*!40000 ALTER TABLE `oikeudet` DISABLE KEYS */;
INSERT INTO `oikeudet` VALUES (1,'1010',2),(2,'1011',2),(3,'1012',2),(4,'1012',3),(5,'1013',7),(6,'1014',8),(7,'1014',9),(8,'1013',9),(9,'1015',4),(10,'1016',5),(11,'1016',6),(12,'1012',12);
/*!40000 ALTER TABLE `oikeudet` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tili`
--

DROP TABLE IF EXISTS `tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tili` (
  `id_tilinumero` int NOT NULL AUTO_INCREMENT,
  `id_asiakas` int NOT NULL,
  `saldo` double NOT NULL,
  `luottoraja` double DEFAULT NULL,
  PRIMARY KEY (`id_tilinumero`,`id_asiakas`),
  KEY `id_asiakas_tili_idx` (`id_asiakas`),
  CONSTRAINT `id_asiakas_tili` FOREIGN KEY (`id_asiakas`) REFERENCES `asiakas` (`id_asiakas`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tili`
--

LOCK TABLES `tili` WRITE;
/*!40000 ALTER TABLE `tili` DISABLE KEYS */;
INSERT INTO `tili` VALUES (2,1,3550,0),(3,1,260,500),(4,4,1663,0),(5,5,786,0),(6,5,0,500),(7,6,1320,0),(8,7,2460,0),(9,7,0,1500),(12,1,400,0);
/*!40000 ALTER TABLE `tili` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tilitapahtumat`
--

DROP TABLE IF EXISTS `tilitapahtumat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tilitapahtumat` (
  `id_tapahtuma` int NOT NULL AUTO_INCREMENT,
  `id_tilinumero` int NOT NULL,
  `id_kortti` char(4) DEFAULT NULL,
  `tapahtuma_aika` timestamp NOT NULL,
  `tapahtuma` varchar(45) NOT NULL,
  `summa` double NOT NULL,
  PRIMARY KEY (`id_tapahtuma`),
  KEY `kortti_tilitapahtumat_idx` (`id_kortti`),
  KEY `tilinumero_tilitapahtumat_idx` (`id_tilinumero`),
  CONSTRAINT `kortti_tilitapahtumat` FOREIGN KEY (`id_kortti`) REFERENCES `kortti` (`id_kortti`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `tilinumero_tilitapahtumat` FOREIGN KEY (`id_tilinumero`) REFERENCES `tili` (`id_tilinumero`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=167 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tilitapahtumat`
--

LOCK TABLES `tilitapahtumat` WRITE;
/*!40000 ALTER TABLE `tilitapahtumat` DISABLE KEYS */;
INSERT INTO `tilitapahtumat` VALUES (2,2,'1012','2022-11-30 08:59:06','nosto',30),(3,2,'1012','2022-11-30 09:15:25','-tilisiirto',200),(5,2,'1012','2022-11-30 09:21:20','nosto',20),(6,2,'1012','2022-11-30 09:24:24','-tilisiirto',10),(8,2,'1012','2022-11-30 10:39:52','-tilisiirto',10),(9,4,'1012','2022-11-30 10:39:52','+tilisiirto',10),(10,2,'1012','2022-11-30 18:11:32','-tilisiirto',10),(11,4,'1012','2022-11-30 18:11:32','+tilisiirto',10),(12,4,'1014','2022-11-30 19:54:45','-tilisiirto',10),(13,2,'1014','2022-11-30 19:54:45','+tilisiirto',10),(14,3,'1012','2022-11-30 19:56:16','nosto',20),(15,2,'1012','2022-11-30 22:12:37','nosto',20),(16,2,'1012','2022-11-30 22:12:57','nosto',20),(17,2,'1012','2022-11-30 22:15:36','nosto',20),(18,2,'1012','2022-11-30 22:15:58','nosto',20),(19,2,'1012','2022-11-30 22:16:05','nosto',50),(20,2,'1012','2022-11-30 22:17:13','nosto',10),(21,2,'1012','2022-11-30 22:17:26','nosto',20),(22,2,'1012','2022-11-30 22:18:10','nosto',10),(23,2,'1012','2022-11-30 22:18:20','nosto',20),(24,2,'1012','2022-11-30 22:18:33','nosto',20),(25,3,'1012','2022-12-01 06:08:49','-tilisiirto',30),(26,2,'1012','2022-12-01 06:08:49','+tilisiirto',30),(27,2,'1012','2022-12-02 23:08:36','nosto',12),(28,2,'1012','2022-12-02 23:08:44','nosto',7),(29,2,'1012','2022-12-02 23:08:52','nosto',10),(30,2,'1012','2022-12-02 23:09:29','-tilisiirto',20),(31,5,'1012','2022-12-02 23:09:29','+tilisiirto',20),(32,2,'1012','2022-12-02 23:09:39','-tilisiirto',3),(33,4,'1012','2022-12-02 23:09:39','+tilisiirto',3),(34,3,'1012','2022-12-03 01:44:37','nosto',10),(35,3,'1012','2022-12-03 01:44:41','-tilisiirto',20),(36,2,'1012','2022-12-03 01:44:41','+tilisiirto',20),(37,3,'1012','2022-12-03 01:44:52','-tilisiirto',33),(38,2,'1012','2022-12-03 01:44:52','+tilisiirto',33),(39,3,'1012','2022-12-03 01:44:58','nosto',5),(40,3,'1012','2022-12-03 01:45:00','nosto',5),(41,3,'1012','2022-12-03 01:45:10','nosto',15),(42,3,'1012','2022-12-03 01:45:37','-tilisiirto',5),(43,2,'1012','2022-12-03 01:45:37','+tilisiirto',5),(44,3,'1012','2022-12-03 01:45:40','nosto',5),(45,3,'1012','2022-12-03 01:46:31','nosto',10),(46,3,'1012','2022-12-04 16:07:22','nosto',2),(47,2,'1012','2022-12-04 16:07:37','nosto',2),(48,2,'1012','2022-12-04 16:13:48','nosto',2),(49,3,'1012','2022-12-04 16:14:01','nosto',2),(50,2,'1012','2022-12-04 16:25:05','nosto',40),(51,2,'1012','2022-12-04 16:25:36','nosto',40),(52,3,'1012','2022-12-04 16:25:47','nosto',100),(53,3,'1012','2022-12-04 16:25:57','nosto',40),(54,3,'1012','2022-12-04 16:27:31','nosto',500),(55,7,'1013','2022-12-04 16:28:24','nosto',40),(56,9,'1013','2022-12-04 16:28:32','nosto',20),(57,7,'1013','2022-12-04 16:28:37','nosto',100),(58,9,'1013','2022-12-04 16:31:09','nosto',40),(59,9,'1013','2022-12-04 16:36:25','-tilisiirto',20),(60,7,'1013','2022-12-04 16:36:25','+tilisiirto',20),(61,3,'1012','2022-12-04 16:37:20','nosto',2),(62,9,'1013','2022-12-04 16:37:43','nosto',40),(63,9,'1013','2022-12-04 16:38:18','nosto',40),(64,9,'1012','2022-12-04 17:13:20','nosto',2),(65,9,'1013','2022-12-04 17:13:33','-tilisiirto',20),(66,7,'1013','2022-12-04 17:13:33','+tilisiirto',20),(67,9,'1012','2022-12-04 17:35:37','nosto',10),(68,7,'1012','2022-12-04 17:37:30','nosto',10),(69,9,'1012','2022-12-04 17:46:01','-tilisiirto',10),(70,2,'1012','2022-12-04 17:46:01','+tilisiirto',10),(71,4,'1012','2022-12-04 17:47:16','-tilisiirto',10),(72,2,'1012','2022-12-04 17:47:16','+tilisiirto',10),(73,2,'1012','2022-12-04 18:18:51','nosto',20),(74,2,'1012','2022-12-04 19:06:06','nosto',100),(75,2,'1012','2022-12-04 19:07:24','nosto',100),(76,2,'1012','2022-12-04 19:07:42','nosto',200),(77,3,'1012','2022-12-04 19:08:10','nosto',100),(78,3,'1012','2022-12-04 19:10:21','nosto',500),(79,3,'1012','2022-12-04 19:12:40','nosto',500),(80,2,'1012','2022-12-04 19:15:25','nosto',20),(81,2,'1012','2022-12-04 19:15:38','nosto',60),(82,2,'1012','2022-12-04 19:15:42','nosto',40),(83,3,'1012','2022-12-04 19:15:58','nosto',200),(84,3,'1012','2022-12-04 19:16:54','nosto',200),(85,3,'1012','2022-12-04 19:18:17','nosto',100),(86,2,'1012','2022-12-04 19:19:38','nosto',40),(87,3,'1012','2022-12-04 19:20:27','nosto',20),(88,3,'1012','2022-12-04 19:23:02','nosto',20),(89,3,'1012','2022-12-04 19:23:05','nosto',20),(90,3,'1012','2022-12-04 19:23:08','nosto',20),(91,3,'1012','2022-12-04 19:31:36','nosto',20),(92,3,'1012','2022-12-04 19:31:52','nosto',40),(93,2,'1012','2022-12-04 19:32:14','nosto',20),(94,2,'1012','2022-12-04 19:32:39','nosto',20),(95,2,'1012','2022-12-04 19:32:42','nosto',200),(96,2,'1012','2022-12-04 19:37:18','nosto',40),(97,3,'1012','2022-12-04 19:37:31','nosto',200),(98,3,'1012','2022-12-04 19:37:58','nosto',100),(99,3,'1012','2022-12-04 19:38:01','nosto',200),(100,2,'1012','2022-12-05 10:46:11','nosto',20),(101,3,'1012','2022-12-05 10:46:49','nosto',500),(102,3,'1012','2022-12-05 10:47:24','nosto',20),(103,3,'1012','2022-12-05 10:47:36','nosto',40),(104,3,'1012','2022-12-05 10:47:43','nosto',200),(105,3,'1012','2022-12-05 10:56:16','nosto',100),(106,3,'1012','2022-12-05 11:01:42','nosto',100),(107,3,'1012','2022-12-05 11:12:11','nosto',100),(108,3,'1012','2022-12-05 11:12:27','nosto',200),(109,3,'1012','2022-12-05 11:12:31','nosto',200),(110,3,'1012','2022-12-05 11:24:23','nosto',123),(111,2,'1011','2022-12-05 12:50:31','nosto',40),(112,12,'1012','2022-12-05 13:33:06','nosto',100),(113,2,'1012','2022-12-05 15:38:37','nosto',40),(114,2,'1012','2022-12-05 16:13:51','nosto',20),(115,2,'1012','2022-12-05 16:21:59','-tilisiirto',20),(116,3,'1012','2022-12-05 16:21:59','+tilisiirto',20),(117,3,'1012','2022-12-05 16:22:28','-tilisiirto',20),(118,2,'1012','2022-12-05 16:22:28','+tilisiirto',20),(119,2,'1012','2022-12-05 16:23:29','-tilisiirto',20),(120,3,'1012','2022-12-05 16:23:29','+tilisiirto',20),(121,2,'1012','2022-12-05 16:23:36','-tilisiirto',20),(122,3,'1012','2022-12-05 16:23:36','+tilisiirto',20),(123,2,'1012','2022-12-05 16:23:43','-tilisiirto',20),(124,3,'1012','2022-12-05 16:23:43','+tilisiirto',20),(125,3,'1012','2022-12-05 16:23:50','-tilisiirto',20),(126,2,'1012','2022-12-05 16:23:50','+tilisiirto',20),(127,2,'1012','2022-12-05 16:38:30','-tilisiirto',20),(128,3,'1012','2022-12-05 16:38:30','+tilisiirto',20),(129,2,'1012','2022-12-05 16:38:33','-tilisiirto',20),(130,3,'1012','2022-12-05 16:38:33','+tilisiirto',20),(131,2,'1012','2022-12-05 16:59:35','-tilisiirto',20),(132,3,'1012','2022-12-05 16:59:35','+tilisiirto',20),(133,3,'1012','2022-12-05 17:01:33','-tilisiirto',30),(134,2,'1012','2022-12-05 17:01:33','+tilisiirto',30),(135,3,'1012','2022-12-05 18:06:31','-tilisiirto',30),(136,2,'1012','2022-12-05 18:06:31','+tilisiirto',30),(137,2,'1012','2022-12-05 18:06:49','-tilisiirto',40),(138,3,'1012','2022-12-05 18:06:49','+tilisiirto',40),(139,2,'1012','2022-12-05 18:30:06','-tilisiirto',40),(140,3,'1012','2022-12-05 18:30:06','+tilisiirto',40),(141,3,'1012','2022-12-05 18:34:44','-tilisiirto',40),(142,2,'1012','2022-12-05 18:34:44','+tilisiirto',40),(143,3,'1012','2022-12-05 18:36:27','-tilisiirto',50),(144,2,'1012','2022-12-05 18:36:27','+tilisiirto',50),(145,2,'1012','2022-12-05 18:47:36','nosto',50),(146,2,'1012','2022-12-05 18:51:55','nosto',50),(147,2,'1012','2022-12-05 19:07:40','-tilisiirto',50),(148,3,'1012','2022-12-05 19:07:40','+tilisiirto',50),(149,2,'1012','2022-12-05 19:16:25','-tilisiirto',50),(150,3,'1012','2022-12-05 19:16:25','+tilisiirto',50),(151,3,'1012','2022-12-05 19:20:33','-tilisiirto',50),(152,2,'1012','2022-12-05 19:20:33','+tilisiirto',50),(153,3,'1012','2022-12-05 19:27:16','-tilisiirto',50),(154,2,'1012','2022-12-05 19:27:16','+tilisiirto',50),(155,3,'1012','2022-12-05 19:28:14','-tilisiirto',50),(156,2,'1012','2022-12-05 19:28:14','+tilisiirto',50),(157,3,'1012','2022-12-05 19:35:32','-tilisiirto',50),(158,2,'1012','2022-12-05 19:35:32','+tilisiirto',50),(159,3,'1012','2022-12-05 19:36:53','-tilisiirto',50),(160,2,'1012','2022-12-05 19:36:53','+tilisiirto',50),(161,3,'1012','2022-12-05 19:44:51','nosto',20),(162,3,'1012','2022-12-05 19:46:11','nosto',40),(163,2,'1012','2022-12-05 19:47:12','-tilisiirto',100),(164,3,'1012','2022-12-05 19:47:12','+tilisiirto',100),(165,3,'1012','2022-12-05 19:47:36','-tilisiirto',50),(166,2,'1012','2022-12-05 19:47:36','+tilisiirto',50);
/*!40000 ALTER TABLE `tilitapahtumat` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'pankki'
--
/*!50003 DROP PROCEDURE IF EXISTS `nosto` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `nosto`(IN kortti CHAR(4), IN ekatili_id INT, IN summa DOUBLE )
BEGIN
  DECLARE test1 INT DEFAULT 0;
  START TRANSACTION;
  IF (select luottoraja from tili where id_tilinumero=ekatili_id >0) THEN 
  COMMIT;
  UPDATE tili SET saldo=saldo+summa WHERE id_tilinumero=ekatili_id AND summa+saldo <= luottoraja;
  ELSE 
COMMIT; 
  UPDATE tili SET saldo=saldo-summa WHERE id_tilinumero=ekatili_id AND summa-saldo <= luottoraja;
  END IF;
  SET test1=ROW_COUNT();
    IF (test1 > 0) THEN   
      COMMIT;    
      INSERT INTO tilitapahtumat(id_tilinumero,id_kortti,tapahtuma,summa,tapahtuma_aika) VALUES(ekatili_id,kortti,'nosto',summa,NOW());
    ELSE
      ROLLBACK;
  END IF;
  end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `siirto` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `siirto`(IN kortti CHAR(4), IN ekatili_id INT, IN tokatili_id INT, IN summa DOUBLE)
BEGIN
  DECLARE test1,test2 INT DEFAULT 0;
  START TRANSACTION;
  IF (select luottoraja from tili where id_tilinumero=ekatili_id >0) THEN 
  UPDATE tili SET saldo=saldo+summa WHERE id_tilinumero=ekatili_id AND summa+saldo <= luottoraja;
  ELSE 
  UPDATE tili SET saldo=saldo-summa WHERE id_tilinumero=ekatili_id AND summa-saldo <= luottoraja;
  END IF;
  SET test1=ROW_COUNT();
  IF (select luottoraja from tili where id_tilinumero=tokatili_id >0 AND test1>0) THEN
  UPDATE tili SET saldo=saldo-summa WHERE id_tilinumero=tokatili_id AND summa-saldo <= 0;
  ELSE
  UPDATE tili SET saldo=saldo+summa WHERE id_tilinumero=tokatili_id;
  END IF;
  SET test2=ROW_COUNT();
    IF (test1 > 0 AND test2 >0) THEN   
      COMMIT;    
      INSERT INTO tilitapahtumat(id_kortti,id_tilinumero,tapahtuma,summa,tapahtuma_aika) VALUES(kortti, ekatili_id,'-tilisiirto',summa,NOW());
      COMMIT;
      INSERT INTO tilitapahtumat(id_tilinumero,id_kortti,tapahtuma,summa,tapahtuma_aika) VALUES(tokatili_id,kortti,'+tilisiirto',summa,NOW());
    ELSE
      ROLLBACK;
  END IF;
  end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-12-05 21:50:35
