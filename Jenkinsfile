pipeline {
  agent none
  stages {
    stage('Verify Dockerfile') {
      agent { dockerfile { filename 'Dockerfile' }}
      steps {
        sh 'python --version'
        SconsCommand('--version')
      }
    }
    stage('Build in parallel'){ parallel {
    
    stage('Simulation'){
      agent { dockerfile { filename 'Dockerfile' }}
          steps { 
            SconsCommand('--debug_build Simulations') 
            SconsCommand('Simulations')
          }
          post{ always {
            archiveArtifacts artifacts: 'build/Simulations*/Simulations', fingerprint: true
          }}
    }
    stage('Console Game'){
      agent { dockerfile { filename 'Dockerfile' }}
          steps { 
            SconsCommand('--debug_build Console_Game') 
            SconsCommand('Console_Game')
            archiveArtifacts artifacts: 'build/Console_Game*/Console_Game', fingerprint: true
          }
    }
    stage('UnitTest'){
      agent { dockerfile { filename 'Dockerfile' }}
      stages{
            stage('build UnitTest') { steps { SconsCommand('UnitTest')}}
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
                  archiveArtifacts artifacts: 'build/UnitTest_release/UnitTest*', fingerprint: true
                  archiveArtifacts artifacts: 'build/UnitTest_release/*xml', fingerprint: true
                }
            }
      }
    }
  }}}
}

def SconsCommand(cmd)
{
    sh 'scons ' + cmd
}
