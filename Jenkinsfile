pipeline {
  agent {
    dockerfile {
      filename 'Dockerfile'
    }

  }
  stages {
    stage('pyhton version') {
      steps {
        sh 'python --version'
        sh 'scons --version'
      }
    }
    stage('build Simulations') {
     steps {
        sh 'scons Simulations'
      }
    }
    stage('build Simulations debug') {
      steps {
        sh 'scons --debug_build Simulations'
      }
    }
    stage('build Console Game') {
      steps {
        sh 'scons Console_Game'
      }
    }
    stage('build Console Game debug') {
      steps {
        sh 'scons --debug_build Console_Game'
      }
    }
    
    stage('build UnitTest') {
      steps {
        sh 'scons UnitTest'
      }
    }
    stage('Test') {
        steps {
          script{
                catchError{
                    sh 'cd build/UnitTest_release && ./UnitTest --gtest_output=xml:unit_test_results.xml'
                }
        }
        step([$class: 'XUnitBuilder',  
            thresholds : [
                [$class: 'FailedThreshold', failureNewThreshold: '', failureThreshold: '0', unstableNewThreshold: '', unstableThreshold: '0'],
                [$class: 'SkippedThreshold', failureNewThreshold: '', failureThreshold: '', unstableNewThreshold: '', unstableThreshold: '']],
             tools : [
                [$class: 'GoogleTestType',  deleteOutputFiles: false, failIfNotNew: false, pattern: 'build/UnitTest_release/unit_test_results.xml', skipNoTestFiles: false, stopProcessingIfError: true]]
        ])
      }
    }
  }
  post {
    always {
        archiveArtifacts artifacts: 'build/Console_Game*/Console_Game', fingerprint: true
        archiveArtifacts artifacts: 'build/Simulations*/Simulations', fingerprint: true
        archiveArtifacts artifacts: 'build/UnitTest_release/UnitTest*', fingerprint: true
        archiveArtifacts artifacts: 'build/UnitTest_release/*xml', fingerprint: true
    }
  }
}