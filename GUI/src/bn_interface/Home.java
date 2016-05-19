/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bn_interface;

import java.awt.Component;
import java.io.File;
import javax.swing.JFileChooser;

/**
 *
 * @author nonwhite
 */
public class Home extends javax.swing.JFrame {

	/**
	 * Creates new form Home
	 */
	public Home() {
		initComponents();
		setDefaults() ;
	}

	/**
	 * This method is called from within the constructor to initialize the form.
	 * WARNING: Do NOT modify this code. The content of this method is always
	 * regenerated by the Form Editor.
	 */
	@SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jFrameApp = new javax.swing.JFrame();
        jTabbedHome = new javax.swing.JTabbedPane();
        jTabbedStructureLearning = new javax.swing.JTabbedPane();
        jPanelGeneralSL = new javax.swing.JPanel();
        jLblDataSet = new javax.swing.JLabel();
        jLblScoreFile = new javax.swing.JLabel();
        jLblBNet = new javax.swing.JLabel();
        jLblDelChar = new javax.swing.JLabel();
        jTxtDataSet = new javax.swing.JTextField();
        jTxtScoresFile = new javax.swing.JTextField();
        jTxtBayesNet = new javax.swing.JTextField();
        jBtnDataSet = new javax.swing.JButton();
        jBtnScoresFile = new javax.swing.JButton();
        jBtnBayesNet = new javax.swing.JButton();
        jChkHasHeader = new javax.swing.JCheckBox();
        jTxtDelimiter = new javax.swing.JTextField();
        jChkSaveFile = new javax.swing.JCheckBox();
        jChkScoresOnly = new javax.swing.JCheckBox();
        jBtnRun = new javax.swing.JButton();
        jChkStructureOptimizationOnly = new javax.swing.JCheckBox();
        jPanelParentSetSelectionSL = new javax.swing.JPanel();
        jLblMethod = new javax.swing.JLabel();
        jLblMaxParentSize = new javax.swing.JLabel();
        jLblRMin = new javax.swing.JLabel();
        jChkWhileCalculatingPrune = new javax.swing.JCheckBox();
        jChkEndOfCalculatingPrune = new javax.swing.JCheckBox();
        jCbxMethod = new javax.swing.JComboBox();
        jSpnMaxParentSize = new javax.swing.JSpinner();
        jSpnRMin = new javax.swing.JSpinner();
        jLblScoringFunction = new javax.swing.JLabel();
        jLblNumThreads = new javax.swing.JLabel();
        jLblTimePerVariable = new javax.swing.JLabel();
        jSpnTimePerVariable = new javax.swing.JSpinner();
        jSpnNumThreads = new javax.swing.JSpinner();
        jCbxScoringFunction = new javax.swing.JComboBox();
        jPanelStructureOptimizationSL = new javax.swing.JPanel();
        jLblAlgorithm = new javax.swing.JLabel();
        jLblNumSolutions = new javax.swing.JLabel();
        jLblMaxIterations = new javax.swing.JLabel();
        jLblInitializer = new javax.swing.JLabel();
        jLblBestScoreCalculator = new javax.swing.JLabel();
        jCbxAlgorithm = new javax.swing.JComboBox();
        jCbxInitializer = new javax.swing.JComboBox();
        jSpnNumSolutions = new javax.swing.JSpinner();
        jSpnMaxIterations = new javax.swing.JSpinner();
        jComboBox3 = new javax.swing.JComboBox();
        jTabbedMultiLabelClassification = new javax.swing.JTabbedPane();
        jPanelGeneralMLC = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jPanelOtherParametersMLC = new javax.swing.JPanel();
        jLabel2 = new javax.swing.JLabel();

        javax.swing.GroupLayout jFrameAppLayout = new javax.swing.GroupLayout(jFrameApp.getContentPane());
        jFrameApp.getContentPane().setLayout(jFrameAppLayout);
        jFrameAppLayout.setHorizontalGroup(
            jFrameAppLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 400, Short.MAX_VALUE)
        );
        jFrameAppLayout.setVerticalGroup(
            jFrameAppLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 300, Short.MAX_VALUE)
        );

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setName("jFrameApp"); // NOI18N

        jLblDataSet.setText("Data Set (.csv)");

        jLblScoreFile.setText("Scores File (.pss)");

        jLblBNet.setText("Bayesian Network (.bnet)");

        jLblDelChar.setText("Delimiter Char.");

        jTxtDataSet.setEditable(false);
        jTxtDataSet.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jTxtDataSetActionPerformed(evt);
            }
        });

        jTxtScoresFile.setEditable(false);

        jTxtBayesNet.setEditable(false);

        jBtnDataSet.setText("...");
        jBtnDataSet.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jBtnDataSetMouseClicked(evt);
            }
        });

        jBtnScoresFile.setText("...");
        jBtnScoresFile.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jBtnScoresFileMouseClicked(evt);
            }
        });

        jBtnBayesNet.setText("...");
        jBtnBayesNet.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jBtnBayesNetMouseClicked(evt);
            }
        });

        jChkHasHeader.setText("Has header?");
        jChkHasHeader.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jChkHasHeaderMouseClicked(evt);
            }
        });

        jChkSaveFile.setText("Save file?");
        jChkSaveFile.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jChkSaveFileMouseClicked(evt);
            }
        });

        jChkScoresOnly.setText("Only Scores?");
        jChkScoresOnly.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jChkScoresOnlyMouseClicked(evt);
            }
        });

        jBtnRun.setText("Run!");
        jBtnRun.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jBtnRunMouseClicked(evt);
            }
        });

        jChkStructureOptimizationOnly.setText("Only Structure Opt.?");
        jChkStructureOptimizationOnly.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jChkStructureOptimizationOnlyMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout jPanelGeneralSLLayout = new javax.swing.GroupLayout(jPanelGeneralSL);
        jPanelGeneralSL.setLayout(jPanelGeneralSLLayout);
        jPanelGeneralSLLayout.setHorizontalGroup(
            jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanelGeneralSLLayout.createSequentialGroup()
                .addGap(30, 30, 30)
                .addGroup(jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                        .addComponent(jLblDataSet, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(jLblScoreFile, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addComponent(jLblBNet, javax.swing.GroupLayout.PREFERRED_SIZE, 167, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(20, 20, 20)
                .addGroup(jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                    .addComponent(jTxtScoresFile, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jTxtBayesNet, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jTxtDataSet, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jBtnBayesNet, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jBtnScoresFile, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jBtnDataSet, javax.swing.GroupLayout.PREFERRED_SIZE, 40, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(30, 30, 30)
                .addGroup(jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(jChkScoresOnly)
                        .addGroup(jPanelGeneralSLLayout.createSequentialGroup()
                            .addGroup(jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                .addComponent(jLblDelChar, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(jChkHasHeader, javax.swing.GroupLayout.DEFAULT_SIZE, 120, Short.MAX_VALUE)
                                .addComponent(jChkSaveFile, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                            .addGap(9, 9, 9)
                            .addComponent(jTxtDelimiter, javax.swing.GroupLayout.PREFERRED_SIZE, 87, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addComponent(jBtnRun, javax.swing.GroupLayout.Alignment.TRAILING))
                    .addComponent(jChkStructureOptimizationOnly))
                .addContainerGap())
        );
        jPanelGeneralSLLayout.setVerticalGroup(
            jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelGeneralSLLayout.createSequentialGroup()
                .addGap(24, 24, 24)
                .addGroup(jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLblDataSet)
                    .addComponent(jTxtDataSet, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jBtnDataSet)
                    .addComponent(jChkHasHeader))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLblDelChar)
                    .addComponent(jTxtDelimiter, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(6, 6, 6)
                .addGroup(jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLblScoreFile)
                    .addComponent(jTxtScoresFile, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jBtnScoresFile)
                    .addComponent(jChkSaveFile))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jChkScoresOnly)
                .addGap(1, 1, 1)
                .addGroup(jPanelGeneralSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLblBNet)
                    .addComponent(jTxtBayesNet, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jBtnBayesNet)
                    .addComponent(jChkStructureOptimizationOnly))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jBtnRun)
                .addContainerGap())
        );

        jTabbedStructureLearning.addTab("General", jPanelGeneralSL);

        jLblMethod.setText("Method");

        jLblMaxParentSize.setText("Max Parent Size");

        jLblRMin.setText("rMin");

        jChkWhileCalculatingPrune.setText("While-calculating prune");
        jChkWhileCalculatingPrune.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jChkWhileCalculatingPruneMouseClicked(evt);
            }
        });

        jChkEndOfCalculatingPrune.setText("End-of-calculating prune");
        jChkEndOfCalculatingPrune.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jChkEndOfCalculatingPruneMouseClicked(evt);
            }
        });

        jCbxMethod.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Sequential" }));

        jSpnMaxParentSize.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(0), Integer.valueOf(0), null, Integer.valueOf(1)));

        jSpnRMin.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(5), Integer.valueOf(5), null, Integer.valueOf(5)));

        jLblScoringFunction.setText("Scoring Function");

        jLblNumThreads.setText("Num Threads");

        jLblTimePerVariable.setText("Time per variable");

        jSpnTimePerVariable.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(0), Integer.valueOf(0), null, Integer.valueOf(1)));

        jSpnNumThreads.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(1), Integer.valueOf(1), null, Integer.valueOf(1)));

        jCbxScoringFunction.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "BIC" }));
        jCbxScoringFunction.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCbxScoringFunctionActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanelParentSetSelectionSLLayout = new javax.swing.GroupLayout(jPanelParentSetSelectionSL);
        jPanelParentSetSelectionSL.setLayout(jPanelParentSetSelectionSLLayout);
        jPanelParentSetSelectionSLLayout.setHorizontalGroup(
            jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelParentSetSelectionSLLayout.createSequentialGroup()
                .addGap(30, 30, 30)
                .addGroup(jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanelParentSetSelectionSLLayout.createSequentialGroup()
                        .addComponent(jChkWhileCalculatingPrune, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addGap(131, 131, 131))
                    .addGroup(jPanelParentSetSelectionSLLayout.createSequentialGroup()
                        .addGroup(jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLblMethod, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jLblMaxParentSize, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jLblRMin, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jCbxMethod, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addGroup(jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                                .addComponent(jSpnRMin, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, 60, Short.MAX_VALUE)
                                .addComponent(jSpnMaxParentSize, javax.swing.GroupLayout.Alignment.LEADING)))
                        .addGap(111, 111, 111)))
                .addGroup(jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                        .addGroup(javax.swing.GroupLayout.Alignment.LEADING, jPanelParentSetSelectionSLLayout.createSequentialGroup()
                            .addComponent(jLblTimePerVariable)
                            .addGap(25, 25, 25)
                            .addComponent(jSpnTimePerVariable, javax.swing.GroupLayout.PREFERRED_SIZE, 60, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addComponent(jChkEndOfCalculatingPrune))
                    .addGroup(jPanelParentSetSelectionSLLayout.createSequentialGroup()
                        .addGroup(jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLblScoringFunction)
                            .addComponent(jLblNumThreads))
                        .addGap(27, 27, 27)
                        .addGroup(jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(jCbxScoringFunction, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addGroup(jPanelParentSetSelectionSLLayout.createSequentialGroup()
                                .addComponent(jSpnNumThreads)
                                .addGap(16, 16, 16)))))
                .addContainerGap(71, Short.MAX_VALUE))
        );
        jPanelParentSetSelectionSLLayout.setVerticalGroup(
            jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelParentSetSelectionSLLayout.createSequentialGroup()
                .addGap(24, 24, 24)
                .addGroup(jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLblMethod)
                    .addComponent(jLblScoringFunction)
                    .addComponent(jCbxMethod, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jCbxScoringFunction, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(20, 20, 20)
                .addGroup(jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLblMaxParentSize)
                    .addComponent(jLblNumThreads)
                    .addComponent(jSpnMaxParentSize, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jSpnNumThreads, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(20, 20, 20)
                .addGroup(jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLblRMin)
                    .addComponent(jSpnRMin, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLblTimePerVariable)
                    .addComponent(jSpnTimePerVariable, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(20, 20, 20)
                .addGroup(jPanelParentSetSelectionSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jChkWhileCalculatingPrune)
                    .addComponent(jChkEndOfCalculatingPrune))
                .addContainerGap(57, Short.MAX_VALUE))
        );

        jTabbedStructureLearning.addTab("Parent Set Selection", jPanelParentSetSelectionSL);

        jLblAlgorithm.setText("Algorithm");

        jLblNumSolutions.setText("Num. solutions");

        jLblMaxIterations.setText("Max Iterations");

        jLblInitializer.setText("Initializer");

        jLblBestScoreCalculator.setText("Best Score Calculator");

        jCbxAlgorithm.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Greedy Search" }));

        jCbxInitializer.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Random" }));

        jSpnNumSolutions.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(1), Integer.valueOf(1), null, Integer.valueOf(1)));

        jSpnMaxIterations.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(1), Integer.valueOf(1), null, Integer.valueOf(1)));

        jComboBox3.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "List" }));

        javax.swing.GroupLayout jPanelStructureOptimizationSLLayout = new javax.swing.GroupLayout(jPanelStructureOptimizationSL);
        jPanelStructureOptimizationSL.setLayout(jPanelStructureOptimizationSLLayout);
        jPanelStructureOptimizationSLLayout.setHorizontalGroup(
            jPanelStructureOptimizationSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelStructureOptimizationSLLayout.createSequentialGroup()
                .addGap(30, 30, 30)
                .addGroup(jPanelStructureOptimizationSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanelStructureOptimizationSLLayout.createSequentialGroup()
                        .addComponent(jLblBestScoreCalculator, javax.swing.GroupLayout.PREFERRED_SIZE, 140, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(jComboBox3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(jPanelStructureOptimizationSLLayout.createSequentialGroup()
                        .addGroup(jPanelStructureOptimizationSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(jLblNumSolutions, javax.swing.GroupLayout.DEFAULT_SIZE, 140, Short.MAX_VALUE)
                            .addComponent(jLblAlgorithm, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addGap(18, 18, 18)
                        .addGroup(jPanelStructureOptimizationSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jCbxAlgorithm, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jSpnNumSolutions, javax.swing.GroupLayout.PREFERRED_SIZE, 60, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(55, 55, 55)
                        .addGroup(jPanelStructureOptimizationSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(jLblMaxIterations, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jLblInitializer, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(jPanelStructureOptimizationSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jCbxInitializer, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jSpnMaxIterations, javax.swing.GroupLayout.PREFERRED_SIZE, 60, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addGap(30, 30, 30))
        );
        jPanelStructureOptimizationSLLayout.setVerticalGroup(
            jPanelStructureOptimizationSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelStructureOptimizationSLLayout.createSequentialGroup()
                .addGap(24, 24, 24)
                .addGroup(jPanelStructureOptimizationSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLblAlgorithm)
                    .addComponent(jLblInitializer)
                    .addComponent(jCbxAlgorithm, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jCbxInitializer, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(30, 30, 30)
                .addGroup(jPanelStructureOptimizationSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLblNumSolutions)
                    .addComponent(jLblMaxIterations)
                    .addComponent(jSpnNumSolutions, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jSpnMaxIterations, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(30, 30, 30)
                .addGroup(jPanelStructureOptimizationSLLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLblBestScoreCalculator)
                    .addComponent(jComboBox3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(81, Short.MAX_VALUE))
        );

        jTabbedStructureLearning.addTab("Structure Optimization", jPanelStructureOptimizationSL);

        jTabbedHome.addTab("Structure Learning", jTabbedStructureLearning);

        jLabel1.setText("In Construction...");

        javax.swing.GroupLayout jPanelGeneralMLCLayout = new javax.swing.GroupLayout(jPanelGeneralMLC);
        jPanelGeneralMLC.setLayout(jPanelGeneralMLCLayout);
        jPanelGeneralMLCLayout.setHorizontalGroup(
            jPanelGeneralMLCLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelGeneralMLCLayout.createSequentialGroup()
                .addGap(30, 30, 30)
                .addComponent(jLabel1)
                .addContainerGap(506, Short.MAX_VALUE))
        );
        jPanelGeneralMLCLayout.setVerticalGroup(
            jPanelGeneralMLCLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelGeneralMLCLayout.createSequentialGroup()
                .addGap(24, 24, 24)
                .addComponent(jLabel1)
                .addContainerGap(207, Short.MAX_VALUE))
        );

        jTabbedMultiLabelClassification.addTab("General", jPanelGeneralMLC);

        jLabel2.setText("In Construction...");

        javax.swing.GroupLayout jPanelOtherParametersMLCLayout = new javax.swing.GroupLayout(jPanelOtherParametersMLC);
        jPanelOtherParametersMLC.setLayout(jPanelOtherParametersMLCLayout);
        jPanelOtherParametersMLCLayout.setHorizontalGroup(
            jPanelOtherParametersMLCLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelOtherParametersMLCLayout.createSequentialGroup()
                .addGap(30, 30, 30)
                .addComponent(jLabel2)
                .addContainerGap(506, Short.MAX_VALUE))
        );
        jPanelOtherParametersMLCLayout.setVerticalGroup(
            jPanelOtherParametersMLCLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelOtherParametersMLCLayout.createSequentialGroup()
                .addGap(24, 24, 24)
                .addComponent(jLabel2)
                .addContainerGap(207, Short.MAX_VALUE))
        );

        jTabbedMultiLabelClassification.addTab("Other parameters", jPanelOtherParametersMLC);

        jTabbedHome.addTab("Multi-Label Classification", jTabbedMultiLabelClassification);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jTabbedHome)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jTabbedHome)
                .addContainerGap())
        );

        getAccessibleContext().setAccessibleName("jFrameApp");

        pack();
    }// </editor-fold>//GEN-END:initComponents

	private void setDefaults(){
		hasHeader = false ;
		saveScoresFile = true ;
		scoresOnly = true ;
	
		whileCalculatingPrune = true ;
		endOfCalculatingPrune = true ;
	}
	
    private void jTxtDataSetActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jTxtDataSetActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jTxtDataSetActionPerformed

    private void jCbxScoringFunctionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCbxScoringFunctionActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jCbxScoringFunctionActionPerformed

    private void jBtnDataSetMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jBtnDataSetMouseClicked
		JFileChooser fChooser = new JFileChooser() ;
		fChooser.setFileSelectionMode( JFileChooser.FILES_ONLY ) ;
		int sel = fChooser.showSaveDialog( null ) ;
		if( sel == 1 ){ // Cancel
			jTxtDataSet.setText( "" ) ;
		}else{ // Select
			File file = fChooser.getSelectedFile() ;
			jTxtDataSet.setText( file.getPath() ) ;
		}
    }//GEN-LAST:event_jBtnDataSetMouseClicked

    private void jBtnScoresFileMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jBtnScoresFileMouseClicked
        JFileChooser fChooser = new JFileChooser() ;
		fChooser.setFileSelectionMode( JFileChooser.FILES_ONLY ) ;
		int sel = fChooser.showSaveDialog( null ) ;
		if( sel == 1 ){ // Cancel
			jTxtScoresFile.setText( "" ) ;
		}else{ // Select
			File file = fChooser.getSelectedFile() ;
			jTxtScoresFile.setText( file.getPath() ) ;
		}
    }//GEN-LAST:event_jBtnScoresFileMouseClicked

    private void jBtnBayesNetMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jBtnBayesNetMouseClicked
        JFileChooser fChooser = new JFileChooser() ;
		fChooser.setFileSelectionMode( JFileChooser.FILES_ONLY ) ;
		int sel = fChooser.showSaveDialog( null ) ;
		if( sel == 1 ){ // Cancel
			jTxtBayesNet.setText( "" ) ;
		}else{ // Select
			File file = fChooser.getSelectedFile() ;
			jTxtBayesNet.setText( file.getPath() ) ;
		}
    }//GEN-LAST:event_jBtnBayesNetMouseClicked

    private void jChkHasHeaderMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jChkHasHeaderMouseClicked
        if( jChkHasHeader.isSelected() ){
			hasHeader = true ;
		}else{
			hasHeader = false ;
		}
    }//GEN-LAST:event_jChkHasHeaderMouseClicked

    private void jChkSaveFileMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jChkSaveFileMouseClicked
        if( jChkSaveFile.isSelected() ){
			saveScoresFile = true ;
		}else{
			saveScoresFile = false ;
		}
    }//GEN-LAST:event_jChkSaveFileMouseClicked

    private void jChkScoresOnlyMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jChkScoresOnlyMouseClicked
        if( jChkScoresOnly.isSelected() ){
			scoresOnly = true ;
		}else{
			scoresOnly = false ;
		}
    }//GEN-LAST:event_jChkScoresOnlyMouseClicked

    private void jBtnRunMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jBtnRunMouseClicked
        System.out.println("Vamo a meterle!");
    }//GEN-LAST:event_jBtnRunMouseClicked

    private void jChkWhileCalculatingPruneMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jChkWhileCalculatingPruneMouseClicked
        if( jChkWhileCalculatingPrune.isSelected() ){
			whileCalculatingPrune = true ;
		}else{
			whileCalculatingPrune = false ;
		}
    }//GEN-LAST:event_jChkWhileCalculatingPruneMouseClicked

    private void jChkEndOfCalculatingPruneMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jChkEndOfCalculatingPruneMouseClicked
        if( jChkEndOfCalculatingPrune.isSelected() ){
			endOfCalculatingPrune = true ;
		}else{
			endOfCalculatingPrune = false ;
		}
    }//GEN-LAST:event_jChkEndOfCalculatingPruneMouseClicked

    private void jChkStructureOptimizationOnlyMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jChkStructureOptimizationOnlyMouseClicked
        if( jChkStructureOptimizationOnly.isSelected() ){
			structureOptimizationOnly = true ;
		}else{
			structureOptimizationOnly = false ;
		}
    }//GEN-LAST:event_jChkStructureOptimizationOnlyMouseClicked

	/**
	 * @param args the command line arguments
	 */
	public static void main(String args[]) {
		/* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
		 * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
		 */
		try {
			for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
				if ("Nimbus".equals(info.getName())) {
					javax.swing.UIManager.setLookAndFeel(info.getClassName());
					break;
				}
			}
		} catch (ClassNotFoundException ex) {
			java.util.logging.Logger.getLogger(Home.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (InstantiationException ex) {
			java.util.logging.Logger.getLogger(Home.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (IllegalAccessException ex) {
			java.util.logging.Logger.getLogger(Home.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (javax.swing.UnsupportedLookAndFeelException ex) {
			java.util.logging.Logger.getLogger(Home.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		}
        //</editor-fold>

		/* Create and display the form */
		java.awt.EventQueue.invokeLater(new Runnable() {
			public void run() {
				new Home().setVisible(true);
			}
		});
	}
	
	// Structure Learning: General Panel
	private boolean hasHeader ;
	private boolean saveScoresFile ;
	private boolean scoresOnly ;
	private boolean structureOptimizationOnly ;
	
	// Structure Learning: Parent Set Selection Panel
	private boolean whileCalculatingPrune ;
	private boolean endOfCalculatingPrune ;
	
	// Structure Learning: Structure Optimization Panel
	

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jBtnBayesNet;
    private javax.swing.JButton jBtnDataSet;
    private javax.swing.JButton jBtnRun;
    private javax.swing.JButton jBtnScoresFile;
    private javax.swing.JComboBox jCbxAlgorithm;
    private javax.swing.JComboBox jCbxInitializer;
    private javax.swing.JComboBox jCbxMethod;
    private javax.swing.JComboBox jCbxScoringFunction;
    private javax.swing.JCheckBox jChkEndOfCalculatingPrune;
    private javax.swing.JCheckBox jChkHasHeader;
    private javax.swing.JCheckBox jChkSaveFile;
    private javax.swing.JCheckBox jChkScoresOnly;
    private javax.swing.JCheckBox jChkStructureOptimizationOnly;
    private javax.swing.JCheckBox jChkWhileCalculatingPrune;
    private javax.swing.JComboBox jComboBox3;
    private javax.swing.JFrame jFrameApp;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLblAlgorithm;
    private javax.swing.JLabel jLblBNet;
    private javax.swing.JLabel jLblBestScoreCalculator;
    private javax.swing.JLabel jLblDataSet;
    private javax.swing.JLabel jLblDelChar;
    private javax.swing.JLabel jLblInitializer;
    private javax.swing.JLabel jLblMaxIterations;
    private javax.swing.JLabel jLblMaxParentSize;
    private javax.swing.JLabel jLblMethod;
    private javax.swing.JLabel jLblNumSolutions;
    private javax.swing.JLabel jLblNumThreads;
    private javax.swing.JLabel jLblRMin;
    private javax.swing.JLabel jLblScoreFile;
    private javax.swing.JLabel jLblScoringFunction;
    private javax.swing.JLabel jLblTimePerVariable;
    private javax.swing.JPanel jPanelGeneralMLC;
    private javax.swing.JPanel jPanelGeneralSL;
    private javax.swing.JPanel jPanelOtherParametersMLC;
    private javax.swing.JPanel jPanelParentSetSelectionSL;
    private javax.swing.JPanel jPanelStructureOptimizationSL;
    private javax.swing.JSpinner jSpnMaxIterations;
    private javax.swing.JSpinner jSpnMaxParentSize;
    private javax.swing.JSpinner jSpnNumSolutions;
    private javax.swing.JSpinner jSpnNumThreads;
    private javax.swing.JSpinner jSpnRMin;
    private javax.swing.JSpinner jSpnTimePerVariable;
    private javax.swing.JTabbedPane jTabbedHome;
    private javax.swing.JTabbedPane jTabbedMultiLabelClassification;
    private javax.swing.JTabbedPane jTabbedStructureLearning;
    private javax.swing.JTextField jTxtBayesNet;
    private javax.swing.JTextField jTxtDataSet;
    private javax.swing.JTextField jTxtDelimiter;
    private javax.swing.JTextField jTxtScoresFile;
    // End of variables declaration//GEN-END:variables
}
