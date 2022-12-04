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
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `oikeudet`
--

LOCK TABLES `oikeudet` WRITE;
/*!40000 ALTER TABLE `oikeudet` DISABLE KEYS */;
INSERT INTO `oikeudet` VALUES (1,'1010',2),(2,'1011',2),(3,'1012',2),(4,'1012',3),(5,'1013',7),(6,'1014',8),(7,'1014',9),(8,'1013',9),(9,'1015',4),(10,'1016',5),(11,'1016',6);
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
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tili`
--

LOCK TABLES `tili` WRITE;
/*!40000 ALTER TABLE `tili` DISABLE KEYS */;
INSERT INTO `tili` VALUES (2,1,20,0),(3,1,0,500),(4,4,1663,0),(5,5,786,0),(6,5,0,500),(7,6,1320,0),(8,7,2460,0),(9,7,1490,1500);
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
) ENGINE=InnoDB AUTO_INCREMENT=73 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tilitapahtumat`
--

LOCK TABLES `tilitapahtumat` WRITE;
/*!40000 ALTER TABLE `tilitapahtumat` DISABLE KEYS */;
INSERT INTO `tilitapahtumat` VALUES (2,2,'1012','2022-11-30 08:59:06','nosto',30),(3,2,'1012','2022-11-30 09:15:25','-tilisiirto',200),(5,2,'1012','2022-11-30 09:21:20','nosto',20),(6,2,'1012','2022-11-30 09:24:24','-tilisiirto',10),(8,2,'1012','2022-11-30 10:39:52','-tilisiirto',10),(9,4,'1012','2022-11-30 10:39:52','+tilisiirto',10),(10,2,'1012','2022-11-30 18:11:32','-tilisiirto',10),(11,4,'1012','2022-11-30 18:11:32','+tilisiirto',10),(12,4,'1014','2022-11-30 19:54:45','-tilisiirto',10),(13,2,'1014','2022-11-30 19:54:45','+tilisiirto',10),(14,3,'1012','2022-11-30 19:56:16','nosto',20),(15,2,'1012','2022-11-30 22:12:37','nosto',20),(16,2,'1012','2022-11-30 22:12:57','nosto',20),(17,2,'1012','2022-11-30 22:15:36','nosto',20),(18,2,'1012','2022-11-30 22:15:58','nosto',20),(19,2,'1012','2022-11-30 22:16:05','nosto',50),(20,2,'1012','2022-11-30 22:17:13','nosto',10),(21,2,'1012','2022-11-30 22:17:26','nosto',20),(22,2,'1012','2022-11-30 22:18:10','nosto',10),(23,2,'1012','2022-11-30 22:18:20','nosto',20),(24,2,'1012','2022-11-30 22:18:33','nosto',20),(25,3,'1012','2022-12-01 06:08:49','-tilisiirto',30),(26,2,'1012','2022-12-01 06:08:49','+tilisiirto',30),(27,2,'1012','2022-12-02 23:08:36','nosto',12),(28,2,'1012','2022-12-02 23:08:44','nosto',7),(29,2,'1012','2022-12-02 23:08:52','nosto',10),(30,2,'1012','2022-12-02 23:09:29','-tilisiirto',20),(31,5,'1012','2022-12-02 23:09:29','+tilisiirto',20),(32,2,'1012','2022-12-02 23:09:39','-tilisiirto',3),(33,4,'1012','2022-12-02 23:09:39','+tilisiirto',3),(34,3,'1012','2022-12-03 01:44:37','nosto',10),(35,3,'1012','2022-12-03 01:44:41','-tilisiirto',20),(36,2,'1012','2022-12-03 01:44:41','+tilisiirto',20),(37,3,'1012','2022-12-03 01:44:52','-tilisiirto',33),(38,2,'1012','2022-12-03 01:44:52','+tilisiirto',33),(39,3,'1012','2022-12-03 01:44:58','nosto',5),(40,3,'1012','2022-12-03 01:45:00','nosto',5),(41,3,'1012','2022-12-03 01:45:10','nosto',15),(42,3,'1012','2022-12-03 01:45:37','-tilisiirto',5),(43,2,'1012','2022-12-03 01:45:37','+tilisiirto',5),(44,3,'1012','2022-12-03 01:45:40','nosto',5),(45,3,'1012','2022-12-03 01:46:31','nosto',10),(46,3,'1012','2022-12-04 16:07:22','nosto',2),(47,2,'1012','2022-12-04 16:07:37','nosto',2),(48,2,'1012','2022-12-04 16:13:48','nosto',2),(49,3,'1012','2022-12-04 16:14:01','nosto',2),(50,2,'1012','2022-12-04 16:25:05','nosto',40),(51,2,'1012','2022-12-04 16:25:36','nosto',40),(52,3,'1012','2022-12-04 16:25:47','nosto',100),(53,3,'1012','2022-12-04 16:25:57','nosto',40),(54,3,'1012','2022-12-04 16:27:31','nosto',500),(55,7,'1013','2022-12-04 16:28:24','nosto',40),(56,9,'1013','2022-12-04 16:28:32','nosto',20),(57,7,'1013','2022-12-04 16:28:37','nosto',100),(58,9,'1013','2022-12-04 16:31:09','nosto',40),(59,9,'1013','2022-12-04 16:36:25','-tilisiirto',20),(60,7,'1013','2022-12-04 16:36:25','+tilisiirto',20),(61,3,'1012','2022-12-04 16:37:20','nosto',2),(62,9,'1013','2022-12-04 16:37:43','nosto',40),(63,9,'1013','2022-12-04 16:38:18','nosto',40),(64,9,'1012','2022-12-04 17:13:20','nosto',2),(65,9,'1013','2022-12-04 17:13:33','-tilisiirto',20),(66,7,'1013','2022-12-04 17:13:33','+tilisiirto',20),(67,9,'1012','2022-12-04 17:35:37','nosto',10),(68,7,'1012','2022-12-04 17:37:30','nosto',10),(69,9,'1012','2022-12-04 17:46:01','-tilisiirto',10),(70,2,'1012','2022-12-04 17:46:01','+tilisiirto',10),(71,4,'1012','2022-12-04 17:47:16','-tilisiirto',10),(72,2,'1012','2022-12-04 17:47:16','+tilisiirto',10);
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
  UPDATE tili SET saldo=luottoraja-summa WHERE id_tilinumero=ekatili_id AND summa-saldo <= luottoraja;
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
  COMMIT;
  UPDATE tili SET saldo=luottoraja-summa WHERE id_tilinumero=ekatili_id AND summa-saldo <= luottoraja;
  ELSE 
COMMIT; 
  UPDATE tili SET saldo=saldo-summa WHERE id_tilinumero=ekatili_id AND summa-saldo <= luottoraja;
  END IF;
  SET test1=ROW_COUNT();
  UPDATE tili SET saldo=saldo+summa WHERE id_tilinumero=tokatili_id;
  SET test2=ROW_COUNT();
    IF (test1 > 0 AND test2 >0) THEN   
      COMMIT;    
      INSERT INTO tilitapahtumat(id_kortti,id_tilinumero,tapahtuma,summa,tapahtuma_aika) VALUES(kortti, ekatili_id,'-tilisiirto',summa,NOW());
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

-- Dump completed on 2022-12-04 19:50:24
